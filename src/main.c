/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "datum.h"

int main() {
  dt_value *v = dt_init();
  v = dt_int(v, 64);
  v = dt_string(v, "test");
  
  printf("Sizeof datum: %lu\n", sizeof(dt_value));
  printf("Type of datum is %d and char data is: \"%s\"\n", dt_type_get(v),
         dt_string_ref(v));

  v = dt_int(v, 32);
  printf("Type of datum is %d and int data is: \"%d\"\n", dt_type_get(v),
         dt_int_get(v));
  
  dt_free(v);

  return EXIT_SUCCESS;
}
