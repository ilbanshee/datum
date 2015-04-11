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
  char* tmp = dt_string_copy(val);
  assert(strcmp(dt_string_ref(val), tmp) == 0);

  char binary[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  val = dt_bstring(val, binary, 10);
  assert(dt_type_get(val) == BSTRING);
  void* btmp = NULL;
  void* ctmp = NULL;
  dt_bstring_copy(val, &ctmp);
  char to_compare[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  assert(dt_bstring_ref(val, &btmp) == 10);
  assert(memcmp(btmp, to_compare, 6) == 0);
  assert(memcmp(ctmp, to_compare, 6) == 0);
  
  dt_free(val);
  free(tmp);
  free(ctmp);
}

int main() {
  test_type_change();
  
  dt_value *v1 = dt_init();
  v1 = dt_int(v1, 64);
  v1 = dt_string(v1, "test");

  printf("Sizeof datum: %lu\n", sizeof(dt_value));
  printf("Type of datum is %d and char data is: \"%s\"\n", dt_type_get(v1),
         dt_string_ref(v1));

  v1 = dt_int(v1, 32);
  printf("Type of datum is %d and int data is: \"%d\"\n", dt_type_get(v1),
         dt_int_get(v1));

  dt_value *v2 = dt_init();
  v2 = dt_int(v2, 23);

  dt_value *v3 = dt_init();
  v3 = dt_int(v3, 231);

  v2 = dt_stack_push(v2, v1);
  v2 = dt_stack_push(v2, v3);

  dt_value *tmp = dt_stack_peek(v2);
  printf("peek at 1 is %d\n", dt_int_get(tmp));
  tmp = dt_stack_peek_at(v2, 2);
  printf("peek at 2 is %d\n", dt_int_get(tmp));
  tmp = dt_stack_peek_at(v2, 3);
  printf("peek at 3 is %d\n", dt_int_get(tmp));
  tmp = dt_stack_peek_at(v2, 4);
  printf("peek at 4 is null: %d\n", tmp == NULL);
  
  tmp = dt_stack_pop(v2);
  while (tmp != NULL) {
    printf("n is %d\n", dt_int_get(tmp));
    dt_free(tmp);
    tmp = dt_stack_pop(v2);
  }

  dt_free(v2);

  return EXIT_SUCCESS;
}
