#pragma once
#ifndef HASH_TABLE
#define HASH_TABLE
#include <stddef.h>
#include <stdbool.h>
#include "common.h"
/**
* @file hash_table.h
* @author Isak Lundback Öst, Olivia Emilsson
* @date 17/9-26
* @brief Simple hash table that maps string keys to integer values.
*
* A hashtable stores key-value pairs and uses a hash function to decide where to store the pairs.
*
*/

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table

size_t ioopm_string_knr_hash(elem_t key);
bool ioopm_string_eq(elem_t a, elem_t b);
 
/// @brief Create a new hash table
/// @return A new empty hash table
/// @param hash_fn a hash function
/// @param key_eq_fn a function to compare two keys
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn,
                                             ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result stores the value of the node if it exists
/// @return true if such key exists, false otherwise
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t* result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key, or 0 if it is not found
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

 
/// @brief Checks if a key exists in a hashtable
/// @param ht hash table
/// @param key the key to check
/// @return true if an entry with the given key exists, false otherwise
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief lookup the number of elements in the hash table (in O(n) time)
/// @param ht hash table
/// @return number of elements in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);
#endif
