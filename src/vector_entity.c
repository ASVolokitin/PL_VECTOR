#ifndef VECTOR_ENTITY
#define VECTOR_ENTITY

#include "../include/vector.h"

struct vector {
    size_t size;
    size_t count;
    size_t next_pointer;
    struct vector_int* data;
};
#endif