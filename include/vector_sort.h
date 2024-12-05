#ifndef VECTOR_SORT_H
#define VECTOR_SORT_H

#include "../include/vector_int.h"

void heapify(struct vector_int *vector, size_t size, size_t root);

void heap_sort(struct vector_int *arr, size_t size);

void vector_swap(struct vector_int *arr, size_t i, size_t j);

#endif
