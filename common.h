#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
* @file common.h
* @author Olivia Emilsson
* @date 1/10-26
* @brief The common types used by the data structures
* Defines the element type elem_t and the function types used for comparing keys and calculating hash values.
*/


//a generic element type
typedef union elem elem_t;

//a function that compares two elements
typedef bool ioopm_eq_function(elem_t a, elem_t b);

//a function that calculates the hash value for an element
typedef size_t ioopm_hash_function(elem_t key);

//Union to store different types of elements
union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *s;
};

#define int_elem(x) ((elem_t) { .i = (x) })
#define bool_elem(x) ((elem_t) { .b = (x) })
#define ptr_elem(x) ((elem_t) { .p = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })

