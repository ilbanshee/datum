/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "datum.h"

void test_type_change() {
  dt_value *val = dt_init();
  assert(!dt_is_know(val));
  val = dt_int(val, 64);
  assert(dt_type_get(val) == INTEGER);
  assert(dt_int_get(val) == 64);
  val = dt_string(val, "test");
  assert(dt_type_get(val) == STRING);
  assert(strcmp(dt_string_ref(val), "test") == 0);
  val = dt_int(val, 32);
  assert(dt_type_get(val) == INTEGER);
  assert(dt_int_get(val) == 32);
  val = dt_string(val, "othertest");
  assert(dt_type_get(val) == STRING);
  assert(strcmp(dt_string_ref(val), "othertest") == 0);
  char *tmp = dt_string_copy(val);
  assert(strcmp(dt_string_ref(val), tmp) == 0);

  char binary[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  val = dt_bstring(val, binary, 10);
  assert(dt_type_get(val) == BSTRING);
  void *btmp = NULL;
  void *ctmp = NULL;
  dt_bstring_copy(val, &ctmp);
  char to_compare[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  assert(dt_bstring_ref(val, &btmp) == 10);
  assert(memcmp(btmp, to_compare, 6) == 0);
  assert(memcmp(ctmp, to_compare, 6) == 0);

  dt_free(val);
  free(tmp);
  free(ctmp);
}

void test_null() {
  dt_value *val = dt_init();
  assert(!dt_is_know(val));

  assert(dt_int_get(val) == INT32_MIN);

  assert(dt_string_ref(val) == NULL);
  assert(dt_string_copy(val) == NULL);

  void *tmp = NULL;
  assert(dt_bstring_ref(val, tmp) == -1);
  assert(tmp == NULL);
  assert(dt_bstring_copy(val, tmp) == -1);
  assert(tmp == NULL);
  
  assert(dt_stack_pop(val) == NULL);
  assert(dt_stack_peek(val) == NULL);

  dt_free(val);
}

void test_stack_init_with_value() {
  dt_value *stack = dt_init();
  dt_value *v0 = dt_init();
  dt_value *v1 = dt_init();
  dt_value *v2 = dt_init();
  dt_value *v3 = dt_init();
  dt_value *v4 = dt_init();
  dt_value *v5 = dt_init();

  stack = dt_int(stack, 1);
  v0 = dt_int(v0, 2);
  v1 = dt_int(v1, 3);
  v2 = dt_int(v2, 5);
  v3 = dt_int(v3, 7);
  v4 = dt_int(v4, 9);
  v5 = dt_int(v5, 11);

  stack = dt_stack_push(stack, v0);
  stack = dt_stack_push(stack, v1);
  stack = dt_stack_push(stack, v2);
  stack = dt_stack_push(stack, v3);
  stack = dt_stack_push(stack, v4);
  stack = dt_stack_push(stack, v5);

  assert(dt_stack_size(stack) == 7);

  dt_value *tmp = dt_stack_pop(stack);
  int counter = 0;
  int to_check[] = { 11, 9, 7, 5, 3, 2, 1 };
  while (tmp != NULL) {
    assert(to_check[counter++] == dt_int_get(tmp));
    dt_free(tmp);
    tmp = dt_stack_pop(stack);
  }
  assert(counter == 7);
  
  dt_free(stack);
}


void test_stack_init_without_value() {
  dt_value *stack = dt_init();
  dt_value *v0 = dt_init();
  dt_value *v1 = dt_init();
  dt_value *v2 = dt_init();
  dt_value *v3 = dt_init();
  dt_value *v4 = dt_init();
  dt_value *v5 = dt_init();

  v0 = dt_int(v0, 2);
  v1 = dt_int(v1, 3);
  v2 = dt_int(v2, 5);
  v3 = dt_int(v3, 7);
  v4 = dt_int(v4, 9);
  v5 = dt_int(v5, 11);

  stack = dt_stack_push(stack, v0);
  stack = dt_stack_push(stack, v1);
  stack = dt_stack_push(stack, v2);
  stack = dt_stack_push(stack, v3);
  stack = dt_stack_push(stack, v4);
  stack = dt_stack_push(stack, v5);

  assert(dt_stack_size(stack) == 6);
  
  dt_value *tmp = dt_stack_pop(stack);
  int counter = 0;
  int to_check[] = { 11, 9, 7, 5, 3, 2 };
  while (tmp != NULL) {
    assert(to_check[counter++] == dt_int_get(tmp));
    dt_free(tmp);
    tmp = dt_stack_pop(stack);
  }
  assert(counter == 6);

  dt_free(stack);
}

int main() {
  test_type_change();
  test_null();
  test_stack_init_with_value();
  test_stack_init_without_value();

  return EXIT_SUCCESS;
}
