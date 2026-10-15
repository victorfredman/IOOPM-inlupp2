#pragma once
#include "common.h"
#include "hash_table.h"

/**
* @file hash_table_struct.h
* @author Olivia Emilsson
* @date 26/9-26
* @brief Hash table struct and definitions
*
*/

#define No_Buckets 17

//Type for storing entries in hash_tables, with key-value pairs as well as a ptr to the next entry
typedef struct entry entry_t;

struct entry
{
    elem_t key;
    elem_t value;
    entry_t *next;
};

//The hashtable struct, cosisting of an array of linked lists (buckets) as well two functions
struct hash_table
{
    entry_t buckets[No_Buckets];
    ioopm_eq_function *key_eq;
    ioopm_hash_function *hash_function;
};
