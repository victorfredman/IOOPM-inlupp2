#include <stdbool.h>
#include "linked_list.h"
#include <stdlib.h>
#include "linked_list_struct.h"

//create a new link
static link_t *link_create(elem_t elem, link_t *next)
{
  link_t *link = malloc(sizeof(link_t));
  link->element = elem;
  link->next = next;
  return link;

}

//get the first element in a linked list
elem_t ioopm_list_head(ioopm_list_t* list){
    return list->first_link->element;
}

//get the last element in a linked list
elem_t ioopm_list_last(ioopm_list_t* list){
    return list->last_link->element;

}

//destroy a link
static void link_destroy(link_t* link){
  free(link);
}

//create a new linked list
ioopm_list_t *ioopm_list_create(void){
    return calloc(1, sizeof(ioopm_list_t));
}

//destroy a list (and all its links)
void ioopm_list_destroy(ioopm_list_t *list){
    link_t *current = list->first_link;

    while (current!=NULL){
        link_t *next = current->next;
        link_destroy(current);
        current = next;
    }
    free(list);
}

//check if list is empty
bool ioopm_list_is_empty(ioopm_list_t *list){
    if (list->size==0){
        return true;
    } else {
        return false;
    }

}

//link a new element to end of list
void ioopm_list_append(ioopm_list_t *list, elem_t value){
    link_t *new_link = link_create(value, NULL);
    if (list->first_link==NULL){
        list->first_link=new_link;
        list->last_link=new_link;
    }
    else{
        //om det finns element tar vi det sista och lägger den nya länken och länkar via next
        list->last_link->next=new_link;
        //måste också "uppdatera" listans last link
        list->last_link=new_link;
    }
    list->size++;

}

//link a new element to the front of the list
void ioopm_list_prepend(ioopm_list_t *list, elem_t value){
    //om tom så gör en första link och sätt som både first och last
    if (list->first_link==NULL){
        link_t* new_first = link_create(value, NULL);
        list->first_link=new_first;
        list->last_link=new_first;

        //annars gör en ny link med gamla first_link som next och sätt som first_link
    } else {
    link_t* first = list->first_link;
    link_t* new_first = link_create(value, first);
    list->first_link=new_first;
    }
    list->size++;
}

//insert a new link at given index
void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value){

    if (index>ioopm_list_size(list)){
        return;
    }
//om tom lägg i början
    if (index==0){
        ioopm_list_prepend(list, value);
    }
     else {//annars gå till linken innan o koppla in mellan
    link_t *previous = list->first_link;
    for (size_t i = 1; i<index; i++){
    previous = previous->next;
    }

    link_t* new_link = link_create(value,previous->next);
    previous->next =new_link;
}

    list->size++;
}

//get size of list
size_t ioopm_list_size(ioopm_list_t *list){
    return list->size;
}

//Tar en lista och ett element, och länkar förbi "nästa" element i listan.
//Returnerar värdet hos länken som tas bort
static elem_t remove_link(ioopm_list_t *list, link_t *prev){
    link_t *to_remove;
//det är första länken, finns ingen prev
    if (prev == NULL){
        to_remove = list->first_link;
        list->first_link = to_remove->next;
    }
//finns en prev
    else{
        to_remove = prev->next;
        prev->next = to_remove->next;
    }
//spara värdet
    elem_t value = to_remove->element;
//om sist, uppdatera last link med linken innan
    if (to_remove == list->last_link){
        list->last_link = prev;
    }
//ta bort, minska size och returnera värdet
    link_destroy(to_remove);
    list->size--;
    

    return value;
}

//remove a link at given index
elem_t ioopm_list_remove(ioopm_list_t *list, size_t index)
{
    if (index == 0){
        return remove_link(list, NULL);
    }

    link_t *previous = list->first_link;
    for (size_t i=1;i<index; i++){
        previous = previous->next;
    }
    return remove_link(list, previous);
}

//return the element at given index
elem_t ioopm_list_get(ioopm_list_t *list, size_t index){
     link_t *current = list->first_link;
    for (size_t i=0;i<index;i++){
         current = current->next;
    }
    //vi har rätt nod i current
    return current->element;

}




