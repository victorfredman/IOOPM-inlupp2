#define No_Buckets 17
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "hash_table_struct.h"

size_t ioopm_string_knr_hash(elem_t key)
{
    size_t result = 0;
    char *str = key.s;

    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char) *str);
        str++;
    }

    return result;
}

size_t ioopm_int_knr_hash(elem_t key)
{
    size_t result = 0;
    result = result * 31 + key.i;
    return result;
}

bool ioopm_int_eq(elem_t a, elem_t b)
{
    return a.i==b.i;
}

bool ioopm_string_eq(elem_t a, elem_t b)
{
    return strcmp(a.s, b.s) == 0;
}