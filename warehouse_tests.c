#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "wh.h"
#include <string.h>

void test_create(){
  wh_t *wt = ioopm_wh_create();
  CU_ASSERT_PTR_NOT_NULL(wt);
  ioopm_wh_destroy(wt);

}

void test_create_cart(){
  wh_t *wh = ioopm_wh_create();
  int new_cart = ioopm_wh_create_cart(wh);
  CU_ASSERT_PTR_NOT_NULL(new_cart);
  CU_ASSERT_EQUAL(wh->carts_id, 1);
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

void test_replenish(void) {
  wh_t *wt = ioopm_wh_create();
  
  ioopm_wh_add_merch(wt, "Banan", "Gul frukt", 10);
  ioopm_wh_add_merch(wt, "Äpple", "Röd frukt", 15);

  bool result1 = ioopm_wh_replenish(wt, "Banan", "A25", 50);
  CU_ASSERT_TRUE(result1);

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
  CU_ASSERT_STRING_EQUAL(merch->name, "Banan");

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
    

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}