#pragma once
#define No_Buckets 17
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "hash_table_struct.h"
#include "hash_table.h"
#include "common.h"

size_t ioopm_string_knr_hash(elem_t key);
size_t ioopm_int_knr_hash(elem_t key);
bool ioopm_string_eq(elem_t a, elem_t b);
bool ioopm_int_eq(elem_t a, elem_t b);
