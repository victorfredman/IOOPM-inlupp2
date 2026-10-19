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

/// @brief Frees the memory allocated for a specific merchandise (including its name, description, and shelves).
/// @param merch Pointer to the merchandise to be destroyed.
void merch_destroy(merch_t *merch);

/// @brief Creates a new, empty shopping cart and adds it to the warehouse's cart system.
/// @param wh Pointer to the warehouse.
/// @return A unique ID (integer) for the newly created shopping cart.
int ioopm_wh_create_cart(wh_t *wh);

/// @brief Creates a new merchandise and allocates memory for it.
/// @param name The name of the merchandise.
/// @param desc The description of the merchandise.
/// @param price The price of the merchandise.
/// @return A pointer to the newly created merchandise.
merch_t* create_merch(char* name, char* desc, int price);

/// @brief Looks up and retrieves a merchandise from the warehouse based on its name.
/// @param wh Pointer to the warehouse.
/// @param name The name of the merchandise to search for.
/// @return A pointer to the merchandise if found, otherwise NULL.
merch_t* ioopm_wh_get_merch(wh_t* wh, char* name);

/// @brief Creates and initializes a new, empty warehouse (setting up all hash tables and counters).
/// @return A pointer to the newly created warehouse.
wh_t* ioopm_wh_create(void);

/// @brief Destroys the warehouse and frees all dynamically allocated memory (including all merchandise, shelves, and carts).
/// @param w Pointer to the warehouse to be destroyed.
void ioopm_wh_destroy(wh_t* w);

/// @brief Adds a new, unique merchandise to the warehouse.
/// @param wh Pointer to the warehouse.
/// @param name The name of the merchandise.
/// @param desc The description of the merchandise.
/// @param price The price of the merchandise.
/// @return true if the merchandise was successfully added, false if a merchandise with the same name already exists.
bool ioopm_wh_add_merch(wh_t *wh, char *name, char *desc, int price);

/// @brief Creates a list of all merchandise currently present in the warehouse.
/// @param wh Pointer to the warehouse.
/// @return A newly allocated linked list containing the merchandise (often sorted alphabetically).
ioopm_list_t *ioopm_wh_list_merchandise(wh_t *wh);

/// @brief Removes a specific merchandise from the warehouse (provided it is not currently in any shopping cart).
/// @param wh Pointer to the warehouse.
/// @param name The name of the merchandise to be removed.
/// @return true if the merchandise was successfully removed, otherwise false.
bool ioopm_wh_remove_merch(wh_t *wh, char* name);

/// @brief Retrieves the stock information (shelves and quantities) for a specific merchandise.
/// @param db Pointer to the warehouse.
/// @param merch_name The name of the merchandise.
/// @return A linked list containing the shelves where the merchandise is stored.
ioopm_list_t *ioopm_show_stock(wh_t *db, char *merch_name);

/// @brief Updates the name, description, and price of an existing merchandise.
/// @param wh Pointer to the warehouse.
/// @param old_name The current name of the merchandise.
/// @param edit A merch_t struct (or pointer) containing the new information.
/// @return A status code (e.g., 0 for success, or another value if the new name is already taken).
int ioopm_wh_edit_merch(wh_t* wh, char* old_name, merch_t* edit);

/// @brief Replenishes the stock of a merchandise on a specific shelf. Creates the shelf if it does not exist.
/// @param wh Pointer to the warehouse.
/// @param merch_name The name of the merchandise to be replenished.
/// @param shelf_name The name of the shelf (e.g., "A25").
/// @param quantity The amount to be added (must be > 0).
/// @return true if successful, false if the shelf is already occupied by a different merchandise.
bool ioopm_wh_replenish(wh_t *wh, char *merch_name, char *shelf_name, int quantity);

/// @brief Reserves a specified quantity of a merchandise and adds it to a specific shopping cart.
/// @param db Pointer to the warehouse.
/// @param cart_id The ID of the shopping cart.
/// @param merch_name The name of the merchandise.
/// @param quantity The amount to be added to the cart.
/// @return A status code (e.g., 0 on success, or an error code if the merchandise is missing or stock is insufficient).
int ioopm_wh_add_to_cart(wh_t* db, int cart_id, char* merch_name, int quantity);