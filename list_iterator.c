#include <stdbool.h>
#include "linked_list.h"
#include <stdlib.h>
#include "linked_list_struct.h"
#include "list_iterator.h"
#include <assert.h>

struct list_iterator {
    ioopm_list_t *list;
    link_t *current;

};


//creates an iterator
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l){
    ioopm_list_iterator_t *iter = calloc(1, sizeof(ioopm_list_iterator_t));
    iter->list = l;
    iter->current = l->first_link;
    return iter;
}

//frees iterator
void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter){
    free(iter);
}

//returns the element of the iterators current node
elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    assert(!ioopm_list_iterator_at_end(iter));
    return iter->current->element;
}

//returns true if iterator is at the end of the list, false otherwise
bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    if (iter->current==0){
        return true;
    } else {
        return false;
    }
}
//advances to the next node
void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter){
    assert(!ioopm_list_iterator_at_end(iter));
    iter->current =iter->current->next;
}






