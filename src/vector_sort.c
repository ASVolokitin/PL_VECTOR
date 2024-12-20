#include "../include/vector_sort.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/vector.h"
#include "../include/vector_int.h"
#include "vector_entity.c"

void heapify(struct vector *vector, size_t size, size_t root) {
  size_t largest = root;

  const size_t l = 2 * root + 1;
  const size_t r = 2 * root + 2;

  if (l < size && vector->data[l].value > vector->data[largest].value) {
    largest = l;
  }

  if (r < size && vector->data[r].value > vector->data[largest].value){
    largest = r;
  }

  if (largest != root) {
    vector_swap(vector, root, largest);
    heapify(vector, size, largest);
  }
}

void heap_sort(struct vector *vector, size_t size) {
  for (int64_t i = size / 2 - 1; i >= 0; i--) {
    heapify(vector, size, i);
  }

  for (size_t i = size - 1; i > 0; i--) {
    vector_swap(vector, 0, i);
    heapify(vector, i, 0);
  }
}