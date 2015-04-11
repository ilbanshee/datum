#include "datum.h"
#include <string.h>
#include <stdlib.h>

static void dt_free_pointers(dt_value *v);

dt_value *dt_init() {
  dt_value *v = calloc(1, sizeof(dt_value));
  v->type = UNKNOWN;
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

bool dt_is_know(dt_value *v) { return v->type != UNKNOWN; }

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
  v->len_or_val = strlen(string) + 1;
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

dt_value *dt_bstring(dt_value *v, void *data, int32_t size) {
  v->type = BSTRING;
  dt_free_pointers(v);
  v->len_or_val = size;
  v->data = malloc(size);
  memcpy(v->data, data, size);

  return v;
}
int32_t dt_bstring_copy(dt_value *v, void *data) {
  if (v->type != BSTRING || data != NULL) {
    return -1;
  }
  data = malloc(v->len_or_val);
  memcpy(data, v->data, v->len_or_val);
  return v->len_or_val;
}

int32_t dt_bstring_ref(dt_value *v, void *data) {
  if (v->type != BSTRING || data != NULL) {
    return -1;
  }
  data = v->data;
  return v->len_or_val;
}

dt_value *dt_stack_push_back(dt_value *v, dt_value *to_push) {
  if (to_push->type == ARRAY) {
    return NULL;
  }
  dt_value *res = v;
  if (v->type != ARRAY) {
    res = dt_init();
    res->type = ARRAY;
    res->len_or_val = 1;
    res->next = v;
  }
  dt_value *it = res;
  while (it->next != NULL) {
    it = it->next;
  }
  res->len_or_val = res->len_or_val + 1;
  it->next = to_push;
  return res;
}

dt_value *dt_stack_push(dt_value *v, dt_value *to_push) {
  if (to_push->type == ARRAY) {
    return NULL;
  }
  dt_value *res = v;
  if (v->type != ARRAY) {
    res = dt_init();
    res->type = ARRAY;
    res->len_or_val = 1;
    res->next = v;
  }
  to_push->next = res->next;
  res->next = to_push;
  res->len_or_val = res->len_or_val + 1;
  return res;
}

dt_value *dt_stack_pop(dt_value *v) {
  if (v->type != ARRAY || v->len_or_val <= 0) {
    return NULL;
  }
  dt_value *result = v->next;
  if (v->len_or_val > 1) {
    v->next = v->next->next;
  } else {
    v->next = NULL;
  }
  result->next = NULL;
  v->len_or_val = v->len_or_val - 1;
  return result;
}

dt_value *dt_stack_peek(dt_value *v) {
  if (v->type != ARRAY || v->len_or_val <= 0) {
    return NULL;
  }
  return v->next;
}

dt_value *dt_stack_peek_at(dt_value *v, int n) {
  if (v->type != ARRAY || v->len_or_val < n) {
    return NULL;
  }
  dt_value *res;
  res = v;
  while(n > 0) {
    res = res->next;
    n--;
  }
  return res;
}
