/**
 * @file warehouse_tests.c
 * @author Victor Fredman & Olivia Emilsson
 * @date 2026-10-29
 * @brief Test file for wh.c
 *
 * This file contains all the tests for the backend file wh.c
 */


#define _XOPEN_SOURCE 700
#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "wh.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define _DEFAULT_SOURCE


void test_create(){
  wh_t *wt = ioopm_wh_create();
  CU_ASSERT_PTR_NOT_NULL(wt);
  ioopm_wh_destroy(wt);

} 

void test_create_cart(){
  wh_t *wh = ioopm_wh_create();
  int new_cart = ioopm_wh_create_cart(wh);
  CU_ASSERT_PTR_NOT_NULL(new_cart);
  ioopm_wh_destroy(wh);
}

void test_destroy(){
  wh_t *wt = ioopm_wh_create();
  CU_ASSERT_PTR_NOT_NULL(wt);
  ioopm_wh_add_merch(wt, "Victor", "trevlig", 2);
  ioopm_wh_destroy(wt);
}

void test_add_merch(){

  wh_t *wt = ioopm_wh_create();
  bool result = ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);
  CU_ASSERT_TRUE(result);
  bool result1 = ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);
  CU_ASSERT_FALSE(result1);
  ioopm_wh_destroy(wt);
    
}

void test_add_remove_merch(){

  wh_t *wt = ioopm_wh_create();
  bool result = ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);
  CU_ASSERT_TRUE(result);
  ioopm_wh_replenish(wt, "Banan", "A1", 100);
  bool result1 = ioopm_wh_remove_merch(wt, "Banan");
  CU_ASSERT_TRUE(result1);
  ioopm_wh_destroy(wt);
    
}

void test_replenish(void) {
  wh_t *wt = ioopm_wh_create();
  
  ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);
  ioopm_wh_add_merch(wt, "Äpple", "Röd frukt", 15);

  bool result1 = ioopm_wh_replenish(wt, "Banan", "A25", 50);
  CU_ASSERT_TRUE(result1);

  ioopm_wh_replenish(wt, "Banan", "A25", 10);
  ioopm_wh_replenish(wt, "Banan", "A2", 5);

  bool result3 = ioopm_wh_replenish(wt, "Äpple", "A25", 10);
  CU_ASSERT_FALSE(result3);

  ioopm_wh_destroy(wt);
}

void test_show_stock(void) {
  
  wh_t *wt = ioopm_wh_create();

  ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);

  ioopm_list_t *result = ioopm_show_stock(wt, "Banan");

  CU_ASSERT_PTR_NOT_NULL(result);

  CU_ASSERT_EQUAL(ioopm_list_size(result), 0);

  ioopm_wh_destroy(wt);
  
}
void test_list_merch(void){
  
  wh_t *wt = ioopm_wh_create();

  ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
  ioopm_wh_add_merch(wt, "Äpple", "Jättegott", 15);
  ioopm_wh_add_merch(wt, "Päron", "Supergott", 20);

  ioopm_list_t *merch_list = ioopm_wh_list_merchandise(wt);

  CU_ASSERT_PTR_NOT_NULL(merch_list);

  CU_ASSERT_EQUAL(3, ioopm_list_size(merch_list));

  ioopm_wh_destroy(wt); 

  ioopm_list_destroy(merch_list);
  
}

void test_get_merch(void){

  wh_t *wt = ioopm_wh_create();
  ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
  ioopm_wh_add_merch(wt, "Äpple", "Jättegott", 15);
  ioopm_wh_add_merch(wt, "Päron", "Supergott", 20);
  merch_t *merch = ioopm_wh_get_merch(wt, "Banan");
  CU_ASSERT_PTR_NOT_NULL(merch);

  ioopm_wh_destroy(wt);

}

void test_edit_merch(void){

  wh_t *wt = ioopm_wh_create();
  ioopm_wh_add_merch(wt, "Äpple", "Smaskigt", 20);
  ioopm_wh_edit_merch(wt, "Äpple", ("Godis"), ("Gott"), 30);
  merch_t *merch = ioopm_wh_get_merch(wt, "Godis");

  CU_ASSERT_PTR_NOT_NULL(merch);

  CU_ASSERT_STRING_EQUAL(ioopm_merch_get_name(merch), "Godis");
  
  ioopm_wh_destroy(wt);
  
}

void test_remove_cart_and_memory(void) {
    wh_t *wh = ioopm_wh_create();
    
    ioopm_wh_add_merch(wh, "Banan", "Gul", 10);
    ioopm_wh_replenish(wh, "Banan", "A01", 10);

    int cart_id = ioopm_wh_create_cart(wh);
    ioopm_wh_add_to_cart(wh, cart_id, "Banan", 3);
    
    ioopm_wh_remove_cart(wh, cart_id);

    int add_result = ioopm_wh_add_to_cart(wh, cart_id, "Banan", 1);
    CU_ASSERT_EQUAL(add_result, -1);

    ioopm_wh_destroy(wh);
}

void test_add_merch_to_cart(void){

  wh_t *wt = ioopm_wh_create();
  int cart = ioopm_wh_create_cart(wt);
  ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
  ioopm_wh_replenish(wt, "Banan", "A1", 10);
  bool result = ioopm_wh_add_to_cart(wt, cart, "Banan", 1);
  CU_ASSERT_EQUAL(result, 0);

  ioopm_wh_destroy(wt);
}

void test_remove_merch_from_cart(void){

  wh_t *wt = ioopm_wh_create();
  int cart = ioopm_wh_create_cart(wt);
  ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
  ioopm_wh_replenish(wt, "Banan", "A1", 10);
  bool result = ioopm_wh_add_to_cart(wt, cart, "Banan", 1);
  bool result1 = ioopm_wh_remove_from_cart(wt, cart, "Banan", 1);
  bool result2 = ioopm_wh_remove_from_cart(wt, cart, "Banan", 2);
  CU_ASSERT_EQUAL(result, 0);
  CU_ASSERT_TRUE(result1);
  CU_ASSERT_FALSE(result2);

  ioopm_wh_destroy(wt);
}

void test_calculate_cost(void){

  wh_t *wt = ioopm_wh_create();
  ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
  ioopm_wh_add_merch(wt, "Äpple", "Jättegott", 15);
  ioopm_wh_add_merch(wt, "Päron", "Supergott", 20);
  int cart = ioopm_wh_create_cart(wt);
  ioopm_wh_replenish(wt, "Banan", "A15", 1);
  ioopm_wh_replenish(wt, "Äpple", "A16", 1);
  ioopm_wh_replenish(wt, "Päron", "A17", 1);
  ioopm_wh_add_to_cart(wt, cart, "Banan", 1);
  ioopm_wh_add_to_cart(wt, cart, "Päron", 1);
  ioopm_wh_add_to_cart(wt, cart, "Äpple", 1);

  int result = ioopm_wh_calculate_cost(wt, cart);

  CU_ASSERT_EQUAL(result, 45);

  ioopm_wh_destroy(wt);
}

void test_checkout(void) {
    wh_t *wt = ioopm_wh_create();

    ioopm_wh_add_merch(wt, "Banan", "Gott", 10);
    ioopm_wh_replenish(wt, "Banan", "A1", 10);

    int cart = ioopm_wh_create_cart(wt);
    CU_ASSERT_EQUAL(ioopm_wh_add_to_cart(wt, cart, "Banan", 10), 0);

    bool checkout = ioopm_wh_cart_checkout(wt, cart);
    CU_ASSERT_TRUE(checkout);

    CU_ASSERT_FALSE(ioopm_wh_cart_checkout(wt, cart));
    CU_ASSERT_EQUAL(ioopm_wh_add_to_cart(wt, cart, "Banan", 1), -1);

    merch_t *merch = ioopm_wh_get_merch(wt, "Banan");
    CU_ASSERT_PTR_NOT_NULL(merch);
    CU_ASSERT_EQUAL(ioopm_merch_get_reserved(merch), 0);

    ioopm_wh_destroy(wt);
}


int main() {
  if (CU_initialize_registry() != CUE_SUCCESS) {
    return CU_get_error(); 
  }

  CU_pSuite my_test_suite = CU_add_suite("wh suite", NULL, NULL);
  if (my_test_suite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_create", test_create) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_create", test_create_cart) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_destroy", test_destroy) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  
  if (CU_add_test(my_test_suite, "test_add_merch", test_add_merch) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_add_remove_merch", test_add_remove_merch) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_replenish", test_replenish) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_show_stock", test_show_stock) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_list_merch", test_list_merch) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_get_merch", test_get_merch) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_add_merch_to_cart", test_add_merch_to_cart) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_remove_merch_from_cart", test_remove_merch_from_cart) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_remove_cart_and_memory", test_remove_cart_and_memory) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_calculate_cost", test_calculate_cost) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(my_test_suite, "test_checkout", test_checkout) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

    if (CU_add_test(my_test_suite, "test_edit_merch", test_edit_merch) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
    
    
    

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}