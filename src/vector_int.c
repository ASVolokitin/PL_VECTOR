#include "../include/vector_int.h"

struct vector_int vint_init(int64_t value, bool defined) {
  struct vector_int vint;
  vint.value = value;
  vint.defined = defined;
  return vint;
}

int64_t vint_get_value(struct vector_int vint) {
  return vint.value;
}

void vint_set_value(struct vector_int vint, int64_t value) {
  vint.value = value;
}

bool vint_is_visited(struct vector_int vint) {
  return vint.defined;
}

void vint_define(struct vector_int vint) {
  vint.defined = true;
}

void vint_undefine(struct vector_int vint) {
  vint.defined = false;
}