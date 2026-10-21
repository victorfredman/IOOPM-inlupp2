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

/// @brief Represents a specific merchandise item in the warehouse.
typedef struct merch merch_t;

/// @brief Represents a physical storage location (shelf) and its current stock quantity.
typedef struct shelf shelf_t;

/// @brief Represents the main warehouse system managing merchandise, shelves, and carts. 
typedef struct wh wh_t;

/// @brief Represents a reserved item inside a shopping cart, tracking the merchandise and quantity.
typedef struct order_item order_item_t;

/// @brief Represents a shopping cart used by a customer to reserve items before checkout.
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
/// @return A status code false or true
bool ioopm_wh_edit_merch(wh_t *wh, char *old_name, char* name, char* desc, int price);

/// @brief Replenishes the stock of a merchandise on a specific shelf. Creates the shelf if it does not exist.
/// @param wh Pointer to the warehouse.
/// @param merch_name The name of the merchandise to be replenished.
/// @param shelf_name The name of the shelf (e.g., "A25").
/// @param quantity The amount to be added (must be > 0).
/// @return true if successful, false if the shelf is already occupied by a different merchandise.
bool ioopm_wh_replenish(wh_t *wh, char *merch_name, char *shelf_name, int quantity);

/// @brief Removes a cart from the warehouse
/// @param wh Pointer to the warehouse  
/// @param cart_id ID of the cart that will be removed
void ioopm_wh_remove_cart(wh_t *wh, int cart_id);

/// @brief Reserves a specified quantity of a merchandise and adds it to a specific shopping cart.
/// @param db Pointer to the warehouse.
/// @param cart_id The ID of the shopping cart.
/// @param merch_name The name of the merchandise.
/// @param quantity The amount to be added to the cart.
/// @return A bool that represents if the adding was successfull or not
bool ioopm_wh_add_to_cart(wh_t* db, int cart_id, char* merch_name, int quantity);

/// @brief Getter function to help ui.c to get the right values
/// @param merch the merch you want to collect information from
/// @return The name of the merch
char *ioopm_merch_get_name(merch_t *merch);

/// @brief Getter function to help ui.c to get the right values
/// @param merch the merch you want to collect information from 
/// @return The price of the merch
int ioopm_merch_get_price(merch_t *merch);

/// @brief Getter function to help ui.c to get the right values
/// @param merch the merch you want to collect information from 
/// @return The description of the merch
char *ioopm_merch_get_desc(merch_t *merch);

/// @brief Removes a number of items from the cart
/// @param db pointer to the warehouse
/// @param cart_id The ID of the shopping cart
/// @param merch_name The name of the merchandise
/// @param quantity The amount to be removed from the cart
/// @return A bool that represents if the adding was successfull or not
bool ioopm_wh_remove_from_cart(wh_t *db, int cart_id, char* merch_name, int quantity);

/// @brief Calculate the costs of a shopping cart
/// @param db pointer to the warehouse
/// @param cart_id The ID of the shopping cart
/// @return The total cost of the shopping cart
int ioopm_wh_calculate_cost(wh_t *db, int cart_id);
