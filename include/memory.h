#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

struct vector_int* allocate_memory(size_t size);

struct vector_int* reallocate_memory(struct vector_int* memory_block, size_t size);

#endif