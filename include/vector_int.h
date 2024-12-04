#ifndef VECTOR_INT_H
#define VECTOR_INT_H

#include <stdint.h>
#include <stdbool.h>

struct vector_int {
  int64_t value;
  bool defined;
};

struct vector_int vint_init(int64_t value, bool defined);

int64_t vint_get_value(struct vector_int vint);

void vint_set_value(struct vector_int vint, int64_t value);

bool vint_is_visited(struct vector_int vint);

void vint_define(struct vector_int vint);

void vint_undefine(struct vector_int vint);

#endif
