#ifndef _DATUM_H_
#define _DATUM_H_
#include <stdint.h>
#include <stdbool.h>

typedef enum dt_type_t { UNKNOWN, INTEGER, STRING, BSTRING, STACK } dt_type;

typedef struct dt_value_t {
  dt_type type;
  int32_t len_or_val;
  void *data;
  struct dt_value_t *next;
} dt_value;

dt_value *dt_init();
void dt_free(dt_value *v);

dt_type dt_type_get(dt_value *v);
bool dt_is_know(dt_value *v);

dt_value *dt_int(dt_value *v, int32_t val);
int32_t dt_int_get(dt_value *v);

dt_value *dt_string(dt_value *v, char *string);
char *dt_string_copy(dt_value *v);
char *dt_string_ref(dt_value *v);

dt_value *dt_bstring(dt_value *v, void *data, int32_t size);
int32_t dt_bstring_copy(dt_value *v, void **data);
int32_t dt_bstring_ref(dt_value *, void **data);

dt_value *dt_stack_push(dt_value *v, dt_value *to_push);
dt_value *dt_stack_push_back(dt_value *v, dt_value *to_push);
dt_value *dt_stack_pop(dt_value *v);

dt_value *dt_stack_peek_at(dt_value *v, int n);
dt_value *dt_stack_peek(dt_value *v);
#endif // _DATUM_H_
