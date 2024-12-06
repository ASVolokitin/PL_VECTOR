#ifndef VECTOR_SORT_H
#define VECTOR_SORT_H

#include "../include/vector.h"

void heapify(struct vector *vector, size_t size, size_t root);

void heap_sort(struct vector *arr, size_t size);

#endif
