#include "hash_table_iterator.h"
#include "hash_table_struct.h"
#include "linked_list_struct.h"
#include <stdlib.h>
#include <assert.h>

struct hash_table_iterator{
    ioopm_hash_table_t *ht;
    int current_bucket;
    entry_t *current_entry;
};

static void advance_iterator_state(ioopm_hash_table_iterator_t *it){
    //make sure iterator is not positioned at end, if failed - crash
    assert(!ioopm_hash_table_iterator_at_end(it) && "At end");
  // advance to the next entry in the bucket
  it->current_entry = it->current_entry->next;
  // if it was null advance to the next bucket
  if (it->current_entry == NULL){
    it->current_bucket += 1;
    // if the next bucket existed, update the current entry
    if (it->current_bucket != No_Buckets){
      it->current_entry = &it->ht->buckets[it->current_bucket];
     }
  }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it){
    while (it->current_bucket!= No_Buckets&&it->current_entry==&it->ht->buckets[it->current_bucket]){
        advance_iterator_state(it);
    }
}
//Create an iterator
ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht){
    ioopm_hash_table_iterator_t *it =malloc(sizeof(ioopm_hash_table_iterator_t));
    it->ht=ht;
    it->current_bucket=0;
    it->current_entry= &ht->buckets[0];
    skip_sentinel_nodes(it);
    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it){
     free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it){
    if (it->current_bucket==No_Buckets){
        return true;
     } else{
        return false;
     } 
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it){
    advance_iterator_state(it);
    skip_sentinel_nodes(it);
}

elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it){
    assert(!ioopm_hash_table_iterator_at_end(it) && "At end");
   return it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it){
    assert(!ioopm_hash_table_iterator_at_end(it) && "At end");
    return it->current_entry->value;
}

