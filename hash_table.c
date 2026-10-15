#define No_Buckets 17
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "hash_table_struct.h"
typedef struct hash_table ioopm_hash_table_t;


static entry_t *entry_create(elem_t key, elem_t value, entry_t *next);
static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key);



static size_t bucket_size(entry_t *entry)
{
    size_t size = 0;

    while (entry != NULL)
    {
        size++;
        entry = entry->next;
    }

    return size;
}


/// creates an entry and assigns its values

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
    entry_t *item = malloc(sizeof(entry_t));

    item->key = key;
    item->value = value;
    item->next = next;
    return item;
}

/// destroys an entry
static void entry_destroy(entry_t* entry){
  free(entry);
}


/// Create a new hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn){
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->hash_function = hash_fn;
    ht->key_eq = key_eq_fn;

    return ht;
 
}

///Delete a hash table and free its memory
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht){
  for(size_t i = 0; i < No_Buckets; i++) {
    entry_t *previous = &ht->buckets[i];
    entry_t *current = previous->next;
    while (current != NULL)
    {
      previous = current;
      current = current->next;
      entry_destroy(previous);
    }
  }
  free(ht);
}


/// add key => value entry in hash table ht
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value){
  //find bucket
  entry_t *previous = find_previous_entry(ht, key);

  //if the key exists, update the value, otherwise, add a new entry to the end of the list
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL);
  }
}

///lookup value for key in hash table ht
/// if the element exists, the result pointer is updated with its value
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
    entry_t *previous = find_previous_entry(ht, key);

    if (previous->next != NULL)
    {
        *result = previous->next->value;
        return true;
    }
    else
    {
        return false;
    }
}

//Uses a key to find the previous entry in ht and return it
static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key) {
  size_t bucket = ht->hash_function(key) % No_Buckets;
    
  entry_t *previous = &ht->buckets[bucket];
  entry_t *current = previous->next;

  while (current != NULL && !ht->key_eq(current->key, key))
  {
    previous = current;
    current = current->next;
  }
  return previous;
}


///remove any mapping from key to a value
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key){

  entry_t* previous=find_previous_entry(ht, key);

  //hittades ej
  if (previous->next==NULL){
    return int_elem(0);
  }

  //om den hittades:
  entry_t*to_remove = previous->next;

  //spara value
  elem_t removed_value = to_remove->value; 

  //hoppa över to_remove noden
  previous->next = to_remove->next;

  entry_destroy(to_remove);
  return removed_value;
}



///ticket 2////

///Checks if a key exists in a hashtable
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
    entry_t *previous = find_previous_entry(ht, key);

    if (previous->next != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///lookup the number of elements in the hash table (in O(n) time)
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht){
    size_t size = 0;
    for (size_t i = 0; i < No_Buckets; i++)
    {
        size+=bucket_size(ht->buckets[i].next);
    }

    return size;
}
