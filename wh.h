#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include "hash_table_struct.h"
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"

typedef struct merch merch_t;

typedef struct shelf shelf_t;
typedef struct wh wh_t;
typedef struct order_item order_item_t;
typedef struct cart cart_t;

struct merch {
    char *name;
    char *desc;
    int price;
    ioopm_list_t *locations;
};

struct shelf {
    char *name;
    size_t size;
};

struct wh {
    ioopm_hash_table_t *name_to_merch;
    ioopm_hash_table_t *shelf_to_name;
};
void merch_destroy(merch_t *merch);
merch_t* create_merch(char* name, char* desc, int price);
merch_t* ioopm_wh_get_merch(wh_t* wh, char* name);
wh_t* ioopm_wh_create(void);
void ioopm_wh_destroy(wh_t* w);
bool ioopm_wh_add_merch(wh_t *wh, char *name, char *desc, int price);
ioopm_list_t *ioopm_wh_list_merchandise(wh_t *wh);
bool ioopm_wh_remove_merch(wh_t *wh, char* name);
ioopm_list_t *ioopm_show_stock(wh_t *db, char *merch_name);
int ioopm_wh_edit_merch(wh_t* wh, char* old_name, merch_t* edit);
bool ioopm_wh_replenish(wh_t *wh, char *merch_name, char *shelf_name, int quantity);