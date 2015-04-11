#ifndef _DATUM_H_
#define _DATUM_H_
#include <stdint.h>

typedef enum dt_type_t { EMPTY, STRING, INTEGER, BSTRING, ARRAY } dt_type;

typedef struct dt_value_t {
  dt_type type;
  int32_t len_or_val;
  void *data;
  struct dt_value_t *next;
} dt_value;

void dt_free(dt_value *v);
dt_value *dt_init();
dt_value *dt_int(dt_value *v, int32_t val);
dt_value *dt_string(dt_value *v, char *string);
dt_type dt_type_get(dt_value *v);
int32_t dt_int_get(dt_value *v);
char *dt_string_copy(dt_value *v);
char *dt_string_ref(dt_value *v);

#endif // _DATUM_H_
