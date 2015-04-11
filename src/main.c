/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "datum.h"

int main() {
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

  dt_value *tmp = dt_stack_pop(v2);
  while (tmp != NULL) {
    printf("n is %d\n", dt_int_get(tmp));
    tmp = dt_stack_pop(v2);
  }

  dt_free(v2);

  return EXIT_SUCCESS;
}
