#include "../include/memory.h"

#include <malloc.h>

#include "../include/util.h"
#include "../include/logger.h"
#include "../include/vector_int.h"

struct vector_int* allocate_memory(size_t size) {
    struct vector_int* memory = malloc(size * sizeof(struct vector_int) * size);
    if (!memory) {
      log_error("memory allocation failed");
      sysexit(ENOMEM);
    }
    return memory;
}

struct vector_int* reallocate_memory(struct vector_int* memory_block, size_t size) {
    if (!memory_block) {
        log_error("Error occured while reallocating vector memory: memory block is undefined.");
        sysexit(ENOMEM);
    }
    memory_block = realloc(memory_block, sizeof(struct vector_int) * size);
    if (!memory_block) {
        log_error("Error occured while reallocating vector memory: not enough memory.");
        sysexit(ENOMEM);
    }
    return memory_block;
}