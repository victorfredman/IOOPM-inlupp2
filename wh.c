#include "wh.h"
#include "linked_list_struct.h"
#include <stdio.h>
#include "linked_list.h"
#include "list_iterator.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "hash_table_struct.h"
#include "hash_table.h"
#include "common.h"
#include "hash_table_iterator.h"
#include "hash_table_struct.h"
#include "utils.h"

wh_t* ioopm_wh_create(void){
    wh_t *wh = malloc(sizeof(wh_t));
    wh->name_to_merch = ioopm_hash_table_create(ioopm_string_knr_hash, ioopm_string_eq);
    wh->shelf_to_name = ioopm_hash_table_create(ioopm_string_knr_hash, ioopm_string_eq);
    return wh;
    //om wh=null???
}

merch_t *create_merch(char *name, char *desc, int price)
{
    merch_t *merch = calloc(1, sizeof(merch_t));

    if (merch == NULL) {
        return NULL;
    }

    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->locations = ioopm_list_create();

    return merch;
}

/*
static shelf_t* shelf_create(char* name, int quantity){
    shelf_t* new_shelf = malloc(sizeof(shelf_t));
    new_shelf->name = name;
    new_shelf->size = quantity;
    return new_shelf;
}*/

static void shelf_destroy(shelf_t *shelf)
{
    if (shelf == NULL) {
        return;
    }
    printf("Destroy shelf: %p, name: %p (%s)\n",(void *) shelf,(void *) shelf->name,shelf->name);
    free(shelf->name);
    free(shelf);
}

void ioopm_wh_destroy(wh_t *wh){

    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(wh->name_to_merch);

    while(!ioopm_hash_table_iterator_at_end(it)){

        merch_t *merch = ioopm_hash_table_iterator_current_value(it).p;

        ioopm_list_iterator_t *list_it = ioopm_list_iterator_create(merch->locations);
        while (!ioopm_list_iterator_at_end(list_it)) {
            shelf_t *shelf = ioopm_list_iterator_current(list_it).p;
            free(shelf);
            ioopm_list_iterator_advance(list_it);
        }
        ioopm_list_iterator_destroy(list_it);

        ioopm_list_destroy(merch->locations);

        free(merch);

        ioopm_hash_table_iterator_advance(it);

    }

    ioopm_hash_table_iterator_destroy(it);

    ioopm_hash_table_destroy(wh->name_to_merch);
    ioopm_hash_table_destroy(wh->shelf_to_name);

    free(wh);
}

void merch_destroy(merch_t *merch)
{
    if (merch == NULL) {
        return;
    }

    free(merch->name);
    free(merch->desc);
    ioopm_list_destroy(merch->locations);
    free(merch);
}


bool ioopm_wh_add_merch(wh_t *wh, char *name, char *desc, int price){

    if(ioopm_hash_table_has_key(wh->name_to_merch, string_elem(name))){

        return false;

    }

    merch_t* new_merch = create_merch(name, desc, price);

    ioopm_hash_table_insert(wh->name_to_merch, string_elem(name), ptr_elem(new_merch));
    return true;
}


merch_t* ioopm_wh_get_merch(wh_t* wh, char* name){
    elem_t result;
    elem_t item = string_elem(name);
    bool found = ioopm_hash_table_lookup(wh->name_to_merch, item, &result);
    if (found){
        merch_t* m = result.p;
        return m;
    }
    else {
        return NULL;
    }
}
bool ioopm_wh_remove_merch(wh_t *wh, char *name)
{
    merch_t *m = ioopm_wh_get_merch(wh, name);

    if (m==NULL) {
        return false;
    }

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(m->locations);
    while (!ioopm_list_iterator_at_end(it)) {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        ioopm_hash_table_remove(wh->shelf_to_name,string_elem(shelf->name));
        shelf_destroy(shelf);
        ioopm_list_iterator_advance(it);
    }

    ioopm_list_iterator_destroy(it);

    ioopm_hash_table_remove(
        wh->name_to_merch,
        string_elem(name)
    );

    merch_destroy(m);
    return true;
}

bool ioopm_wh_replenish(wh_t *wh, char *merch_name, char *shelf_name, int quantity)
{
    // 1. Kolla om varan finns
    elem_t merch_result;
    if (!ioopm_hash_table_lookup(wh->name_to_merch, string_elem(merch_name), &merch_result)) {
        return false;
    }
    merch_t *merch = merch_result.p;

    // 2. Kolla vem som äger hyllan (om den redan finns)
    elem_t shelf_result;
    if (ioopm_hash_table_lookup(wh->shelf_to_name, string_elem(shelf_name), &shelf_result)) {
        char *current_merch_on_shelf = shelf_result.s;
        
        if (strcmp(current_merch_on_shelf, merch_name) != 0) {
            return false;
        }
    } // <-- Här tog jag bort det extra } som stängde funktionen för tidigt!

    // 3. Leta i varans befintliga hyllor
    bool shelf_found = false;
    ioopm_list_iterator_t *it = ioopm_list_iterator_create(merch->locations); 

    // VIKTIGT: "Så länge vi INTE är i slutet" (märk utropstecknet!)
    while (!ioopm_list_iterator_at_end(it)) {

        shelf_t *current_shelf = ioopm_list_iterator_current(it).p; 
        if (strcmp(current_shelf->name, shelf_name) == 0) {
            current_shelf->size += quantity;
            shelf_found = true;
            break;
        }

        ioopm_list_iterator_advance(it);
    }
    
    ioopm_list_iterator_destroy(it);

    // 4. Lägg till hyllan om den var ny
    if (!shelf_found) {
        shelf_t *new_shelf = calloc(1, sizeof(shelf_t));
        new_shelf->name = strdup(shelf_name); 
        new_shelf->size = quantity;         

        ioopm_list_append(merch->locations, ptr_elem(new_shelf));
        ioopm_hash_table_insert(wh->shelf_to_name, string_elem(new_shelf->name), string_elem(merch->name));
    }

    return true;
}

ioopm_list_t *ioopm_wh_list_merchandise(wh_t *wh){
    
    ioopm_list_t *merch_list = ioopm_list_create();

    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(wh->name_to_merch);

    while(!ioopm_hash_table_iterator_at_end(it)){

        merch_t *merch = ioopm_hash_table_iterator_current_value(it).p;

        ioopm_list_append(merch_list, ptr_elem(merch));

        ioopm_hash_table_iterator_advance(it);
    }

    ioopm_hash_table_iterator_destroy(it);

    return merch_list;

}


int ioopm_wh_edit_merch(wh_t *wh, char *old_name, merch_t *edit)
{
    elem_t result;

    if (!ioopm_hash_table_lookup(wh->name_to_merch, string_elem(old_name), &result)){
        return -1;
    }

    if (strcmp(old_name, edit->name) != 0 && ioopm_hash_table_has_key(wh->name_to_merch, string_elem(edit->name))){
        return -2;
    }

    merch_t *old_merch = result.p;
    ioopm_hash_table_remove(wh->name_to_merch, string_elem(old_name));

    free(old_merch->name);
    free(old_merch->desc);

    old_merch->name = strdup(edit->name);
    old_merch->desc = strdup(edit->desc);
    old_merch->price = edit->price;

    ioopm_hash_table_insert(wh->name_to_merch,string_elem(old_merch->name),ptr_elem(old_merch));

    return 0;
}
    
ioopm_list_t *ioopm_show_stock(wh_t *db, char *merch_name){

    merch_t* merch = ioopm_wh_get_merch(db, merch_name);

    return merch->locations;
}

int wh_count_stock(merch_t *merch){
    int total = 0;

    ioopm_list_iterator_t *it =
        ioopm_list_iterator_create(merch->locations);

    while (!ioopm_list_iterator_at_end(it))
    {
        elem_t elem = ioopm_list_iterator_current(it);
        shelf_t *shelf = elem.p;
        total += shelf->size;
        ioopm_list_iterator_advance(it);
    }
    ioopm_list_iterator_destroy(it);
    return total;
}








    
 
