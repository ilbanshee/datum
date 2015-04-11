#include "datum.h"
#include <string.h>
#include <stdlib.h>

static void dt_free_pointers(dt_value *v);

dt_value *dt_init() {
  dt_value *v = calloc(1, sizeof(dt_value));
  v->type = EMPTY;
  v->len_or_val = -1;
  v->data = NULL;
  v->next = NULL;

  return v;
}

void dt_free(dt_value *v) {
  if (v == NULL) {
    return;
  }
  if (v->next != NULL) {
    dt_free(v->next);
  }
  free(v->data);
  free(v);
}

static void dt_free_pointers(dt_value *v) {
  free(v->data);
  v->data = NULL;
  dt_free(v->next);
  v->data = NULL;
}

dt_type dt_type_get(dt_value *v) { return v->type; }

dt_value *dt_int(dt_value *v, int32_t val) {
  v->type = INTEGER;
  v->len_or_val = val;
  dt_free_pointers(v);

  return v;
}

int32_t dt_int_get(dt_value *v) {
  if (v->type != INTEGER) {
    return INT32_MIN;
  }
  return v->len_or_val;
}

dt_value *dt_string(dt_value *v, char *string) {
  v->type = STRING;
  dt_free_pointers(v);
  v->len_or_val = strlen(string)+1;
  v->data = malloc(v->len_or_val);
  strncpy(v->data, string, v->len_or_val);

  return v;
}

char *dt_string_copy(dt_value *v) {
  if (v->type != STRING) {
    return NULL;
  }
  char *res = malloc(v->len_or_val);
  strncpy(res, v->data, v->len_or_val);
  return res;
}

char *dt_string_ref(dt_value *v) {
  if (v->type != STRING) {
    return NULL;
  }
  return v->data;
}
