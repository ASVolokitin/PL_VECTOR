#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

#include "vector_int.h"

struct vector {
    size_t size;
    size_t count;
    size_t next_pointer;
    struct vector_int* data;
};

struct vector* vector_create(size_t size);

void vector_destroy(struct vector* vector);

int64_t vector_get_value(const struct vector* vector, size_t index);

int64_t vector_get_value_if_defined(const struct vector* vector, size_t index);

void vector_set_value(struct vector* vector, size_t index, int64_t value);

void vector_delete_value(struct vector* vector, size_t index);

void vector_push_back(struct vector* vector, int64_t value);

int64_t vector_pop_back(struct vector* vector);

size_t vector_get_size(const struct vector* vector);

void vector_set_size(struct vector* vector, size_t new_size);

size_t vector_get_count(const struct vector* vector);

void vector_set_count(struct vector* vector, size_t size);

size_t vector_get_next_pointer(const struct vector* vector);

void vector_set_next_pointer(struct vector* vector, size_t next_pointer);

void vector_inc_count(struct vector* vector);

void vector_dec_count(struct vector* vector);

void vector_inc_next_pointer(struct vector* vector);

void vector_dec_next_pointer(struct vector* vector);

struct vector_int* vector_get_data_ptr(const struct vector* vector);

void vector_set_data_ptr(struct vector* vector, struct vector_int* data);

void vector_concatenate(struct vector* vector, struct vector* additional_vector);

void vector_print(const struct vector* vector, const char* filename);

void vector_print_defined(const struct vector* vector, const char* filename);

void vector_show(const struct vector* vector);

void vector_show_defined(const struct vector* vector);

void vector_sort(struct vector* vector);

#endif