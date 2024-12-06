#include "../include/vector.h"

#include <malloc.h>
#include <stdio.h>

#include "../include/logger.h"
#include "../include/memory.h"
#include "../include/util.h"
#include "../include/vector_int.h"
#include "../include/vector_sort.h"

static void fill_with_zeros(struct vector* vector, size_t begin, size_t end) {
  printf("Filling with zeros from %zu to %zu ...\n", begin, end);
  for (size_t i = begin; i < end; ++i) {
    vector->data[i] = vint_init(0, false);
  }
}

struct vector* vector_create(size_t size) {
  printf("Creating a vector with %zu elements.\n", size);
  struct vector* vector = malloc(sizeof(struct vector));
  if (!vector) {
    log_error("Error occured allocating memory for vector");
  }
  vector_set_data_ptr(vector, allocate_memory(size));
  vector_set_count(vector, 0);
  vector->size = size;
  fill_with_zeros(vector, 0, size);
  vector_set_next_pointer(vector, size);
  return vector;
}

void vector_destroy(struct vector* vector) {
  printf("Destroying vector...\n");
  free(vector_get_data_ptr(vector));
  free(vector);
}

static struct vector_int vector_get_vint(const struct vector* vector, size_t index) {
  if (index >= vector->size) {
    log_error("Error occured while getting value: index out of range");
    sysexit(EFAULT);
  }
  return vector->data[index];
}

int64_t vector_get_value(const struct vector* vector, size_t index) {
  struct vector_int vint = vector_get_vint(vector, index);
  return vint.value;
}

int64_t vector_get_value_if_defined(const struct vector* vector, size_t index) {
  struct vector_int vint = vector_get_vint(vector, index);
  if (vint.defined) return vint.value;
  printf("Error occured while getting value from index %zu: value is undefined\n", index);
  sysexit(EFAULT);
  return 0;
}

void vector_set_value(struct vector* vector, size_t index, int64_t value) {
  if (index >= vector->size) {
    log_info("Not enough memory, reallocating ...");
    vector_set_size(vector, vector_get_size(vector) * 2 ? vector_get_size(vector) * 2 : 1);
  }
  if (!vector_get_vint(vector, index).defined) {
    vector->data[index] = vint_init(value, true);
    vector_inc_count(vector);
  }
  if (index >= vector_get_next_pointer(vector)) {
    vector_set_next_pointer(vector, index + 1);
  }
  vector->data[index].value = value;
}

void vector_delete_value(struct vector* vector, size_t index) {
  if (index >= vector->size) {
    printf("Error occured while deleting value: index out of range");
    sysexit(EFAULT);
  }
  if (vector_get_vint(vector, index).defined) {
    vector_dec_count(vector);
    vector->data[index] = vint_init(0, false);
    vector_dec_next_pointer(vector);
    for (size_t i = index; i < vector_get_next_pointer(vector); ++i) {
      vector_swap(vector, i, i+1);
    }
    return;
  }
  printf("Element with index %zu was not deleted because it was not defined\n", index);
}

void vector_push_back(struct vector* vector, int64_t value) {
  vector_set_value(vector, vector_get_next_pointer(vector), value);
}

int64_t vector_pop_back(struct vector* vector) {
  if (vector_get_size(vector) == 0) {
    printf("Popping back failed: vector is empty\n");
    sysexit(EFAULT);
  }
  int64_t value = vector_get_value(vector, vector_get_next_pointer(vector) - 1);
  vector_delete_value(vector, vector_get_next_pointer(vector) - 1);
  return value;
}

size_t vector_get_size(const struct vector* vector) {
  return vector->size;
}

void vector_set_size(struct vector* vector, size_t new_size) {
  size_t old_size = vector_get_size(vector);
  if (old_size != new_size) {
    vector_set_data_ptr(vector, reallocate_memory(vector_get_data_ptr(vector), new_size));
    if (old_size < new_size) fill_with_zeros(vector, vector_get_size(vector), new_size);
    vector->size = new_size;
    printf("Resizing vector, now used: %zu of %zu\n", vector_get_count(vector), vector_get_size(vector));
  }
}

size_t vector_get_count(const struct vector* vector) {
  return vector->count;
}

void vector_set_count(struct vector* vector, size_t count) {
  vector->count = count;
}

size_t vector_get_next_pointer(const struct vector* vector) {
  return vector->next_pointer;
}

void vector_set_next_pointer(struct vector* vector, size_t next_pointer) {
  vector->next_pointer = next_pointer;
}

void vector_inc_count(struct vector* vector) {
  vector->count += 1;
}

void vector_dec_count(struct vector* vector) {
  vector->count -= 1;
}

void vector_inc_next_pointer(struct vector* vector) {
  vector->next_pointer += 1;
}

void vector_dec_next_pointer(struct vector* vector) {
  vector->next_pointer -= 1;
}

struct vector_int* vector_get_data_ptr(const struct vector* vector) {
  return vector->data;
}

void vector_set_data_ptr(struct vector* vector, struct vector_int* data) {
  vector->data = data;
}

void vector_concatenate(struct vector* vector, struct vector* additional_vector) {
  for (size_t i = 0; i < vector_get_size(additional_vector); i++) {
    vector_push_back(vector, vector_get_value(additional_vector, i));
  }
}

void vector_print(const struct vector* vector, const char* filename) {
  FILE* f = fopen(filename, "wb");
  for (size_t i = 0; i < vector_get_next_pointer(vector); i++) {
    fprintf(f, "%lld\n", vector_get_value(vector, i));
  }
  fclose(f);
}

void vector_print_defined(const struct vector* vector, const char* filename) {
  FILE* f = fopen(filename, "wb");
  for (size_t i = 0; i < vector_get_next_pointer(vector); i++) {
    if (vector_get_vint(vector, i).defined) fprintf(f, "%lld\n", vector_get_value(vector, i));
  }
  fclose(f);
}

void vector_show(const struct vector* vector) {
  for (size_t i = 0; i < vector_get_size(vector); i++) {
    printf("%lld\n", vector_get_value(vector, i));
  }
}

struct vector* vector_slice(struct vector* vector, size_t start, size_t end) {
  if (end >= vector_get_size(vector)) end = vector_get_size(vector) - 1;
  struct vector* slice = vector_create(0);
  size_t count = 0;
  for (size_t i = start; i < end; i++) {
    vector_push_back(slice, vector_get_value(vector, i));
    if (vector_get_vint(vector, i).defined) {count++;}
  }
  vector_set_count(slice, count);
  vector_set_next_pointer(slice, vector_get_size(slice));
  return slice;
}

void vector_show_defined(const struct vector* vector) {
  for (size_t i = 0; i < vector_get_next_pointer(vector); i++) {
    if (vector_get_vint(vector, i).defined) printf("%lld\n", vector_get_value(vector, i));
  }
}

void vector_sort(struct vector* vector) {
  if (vector_get_size(vector) > 0) heap_sort(vector, vector_get_size(vector));
  else printf("Sorting vector stopped: vector is empty\n");
}

void vector_swap(struct vector *vector, size_t i, size_t j) {
  struct vector_int tmp = vector->data[i];
  vector->data[i].value = vector->data[j].value;
  vector->data[i].defined = vector->data[j].defined;
  vector->data[j].value = tmp.value;
  vector->data[j].defined = tmp.defined;
}