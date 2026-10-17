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
#include <ctype.h>

void print_menu(){
    printf("--------------------\n");
    printf("        MENU   \n");
    printf("--------------------\n");
    printf("(A) Add merchandise\n");
    printf("(L) List merchandise\n");
    printf("(D) Remove merchandise\n");
    printf("(E) Edit merchandise\n");
    printf("(S) Show stock\n");
    printf("(P) Replenish\n");
    printf("(C) Create cart\n");
    printf("(R) Remove cart\n");
    printf("(+) Add to cart\n");
    printf("(-) Remove from cart\n");
    printf("(=) Calculate cost\n");
    printf("(O) Checkout\n");
};



char ask_question_menu(void){
    const char *valid_chars = "ALTDREGPCHS+-=O";
    
    while (true){
        print_menu();
        char *answer = ask_question_string("\nOPTION: ");
        if (answer == NULL){
            continue;
        }

        if (answer[0] != '\0' && answer[1] == '\0'){
            char choice = (char) toupper((unsigned char) answer[0]);
            free(answer);

            for (int i = 0; valid_chars[i] != '\0'; i++)
            {
                if (choice == valid_chars[i]){
                    return choice;
                }
            }
        }
        else{
            free(answer);
        }
        printf("Invalid option\n");
    }
}

void ui_add_merch(wh_t* db){
    printf("--------------------\n");
    printf("      ADD MERCH     \n");
    char* name = ask_question_string("Name: ");
    char* desc = ask_question_string("Description: ");
    int price = ask_question_int("Price: ");
    bool success = ioopm_wh_add_merch(db, name, desc, price);
    if (!success){
        printf("Merch already exists\n");
        free(name);
        free (desc);
    } else{
        printf("Merch has been added\n");
    }
}

void ui_list_merch(wh_t *db){
    printf("--------------------\n");
    printf("       MERCH:     \n");
    ioopm_list_t *merch_list = ioopm_wh_list_merchandise(db);
    ioopm_list_iterator_t *iter =
        ioopm_list_iterator_create(merch_list);
    while (!ioopm_list_iterator_at_end(iter)) {
        elem_t current = ioopm_list_iterator_current(iter);
        merch_t *item = current.p;
        printf("%s\n", item->name);
        ioopm_list_iterator_advance(iter);
    }
    ioopm_list_iterator_destroy(iter);
    ioopm_list_destroy(merch_list);
}

void ui_remove_merch(wh_t *db)
{
    printf("--------------------\n");
    printf("    REMOVE MERCH     \n");
    char *name = ask_question_string("Merch to remove: ");
    merch_t *merch =ioopm_wh_get_merch(db, name);
    if (merch == NULL) {
        printf("Merch doesn't exist\n");
        free(name);
        return;
    }
    if (ioopm_wh_remove_merch(db, name)) {
        printf("Merch has been removed\n");
    } else {
        printf("Could not remove merch\n");
    }

    free(name);
}

static bool confirm_edit(char *name, char *desc, int price){
    printf("\nEdited merch:");
    printf("\nName: %s", name);
    printf("\nDescription: %s", desc);
    printf("\nPrice: %d\n", price);
    char *answer = ask_question_string("(Y) Confirm edit?: ");
    bool confirmed = toupper(answer[0]) == 'Y';
    free(answer);
    return confirmed;
}

void ui_edit_merch(wh_t *db)
{
    printf("--------------------\n");
    printf("     EDIT MERCH     \n");
    char *old_name = ask_question_string("Choose merch to edit: ");
    char *name = ask_question_string("New name: ");
    char *desc = ask_question_string("New description: ");
    int price = ask_question_int("New price: ");

    if (confirm_edit(name, desc, price)){

        int result = ioopm_wh_edit_merch(db, old_name, name, desc, price);

        if (result==0){
            printf("Merch edited successfully!\n");
        }
        else if (result==-1){
            printf("Merch not found.\n");
        }
        else if (result==-2){
            printf("Name is already in use.\n");
        }
    }
    else{
        printf("Edit cancelled.\n");
    }

    free(old_name);
}

void ui_replenish(wh_t* db){
    char* merch_name = ask_question_string("Merch: ");
    char* shelf_name = ask_question_string("Shelf: ");
    int increase = ask_question_int("Increase by: ");

    if (!ioopm_wh_replenish(db, merch_name, shelf_name, increase)){
        printf("Fail\n");
    }
    else {
        printf("Stock updated\n");
    }
    free(shelf_name);
    free(merch_name);
    return;
    }

void ui_show_stock(wh_t* db){
    printf("--------------------\n");
    printf("      SHOW STOCK    \n");
    char* answer= ask_question_string("Merch: ");
    ioopm_list_t* locs = ioopm_show_stock(db, answer);

    if (locs->size ==0){
        printf("No items\n");
    } else {
    ioopm_list_iterator_t* iter = ioopm_list_iterator_create(locs);
    while (!ioopm_list_iterator_at_end(iter)){
        elem_t current = ioopm_list_iterator_current(iter);
        shelf_t* shelf = current.p;
        printf("SHELF: %s ", shelf->name);
        printf("QUANTITY: %zu\n", shelf->size);
        ioopm_list_iterator_advance(iter);
    }
     ioopm_list_iterator_destroy(iter);
    }

   
}

void ui_create_cart(wh_t *db){
    printf("--------------------\n");
    printf("     CREATE CART    \n");

    int id = ask_question_int("\nCart id: ");
    if (ioopm_hash_table_has_key(db->carts, int_elem(id))){
        printf("ID already exists\n");
        return;
    }
    cart_t *cart = ioopm_wh_create_cart(id);

    ioopm_hash_table_insert(db->carts, int_elem(id), ptr_elem(cart));
    printf("Cart created\n");
}

void ui_remove_cart(wh_t* db){
    printf("--------------------\n");
    printf("     REMOVE CART    \n");
    int id = ask_question_int("ID to remove: ");
    if (!ioopm_hash_table_has_key(db->carts, int_elem(id))){
        printf("ID %d doesn't exist", id);
    }
    else {
        ioopm_hash_table_remove(db->carts, int_elem(id));
        printf("Cart (ID:%d) removed\n", id);
    }
}




void event_loop(wh_t* db)
{
    while (true){

    if (db == NULL){
        return;
    }

    char answer = ask_question_menu();
    if (answer=='A'){
        ui_add_merch(db);
    }
    if (answer=='L'){
        ui_list_merch(db);
    }
    if (answer=='D'){
        ui_remove_merch(db);
    }
    if (answer=='E'){
        ui_edit_merch(db);
    }
    if (answer=='P'){
        ui_replenish(db);
    }
    if (answer=='S'){
        ui_show_stock(db);
    }
    if (answer=='C'){
        ui_create_cart(db);
    }
    if (answer=='R'){
        ui_remove_cart(db);
    }

    }
}

//bara för att testa list funktionerna, går ej att freea dom elr deras fält då dom ej är dynamiskt allokerade
static void stock(wh_t* db){
    ioopm_wh_add_merch(db, "Kaffe", "Mörkrost", 10);
    ioopm_wh_add_merch(db, "Te", "Svart", 5);
    ioopm_wh_add_merch(db, "Olivia", "lol", 5);
}


int main(){
    wh_t *wh = ioopm_wh_create();
    stock(wh);
    event_loop(wh);
    ioopm_wh_destroy(wh);
}


