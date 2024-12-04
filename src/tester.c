#include "../include/tester.h"

#include <stdio.h>

void vector_test(struct vector *vector) {
    size_t capacity = vector_get_size(vector);

    vector_set_value(vector, 0, -20);
    printf("Got value: %lld\n", vector_get_value(vector, 0));
    printf("Got value: %lld\n", vector_get_value(vector, 1));

    printf("\nTrying to get out of bounds of vector...\n");
    printf("Current last used index: %lld\n", vector_get_next_pointer(vector) - 1);
    for (size_t i = vector_get_next_pointer(vector); i < capacity * 3; i++) {
        vector_set_value(vector, i * 3, i * 2);
        vector_push_back(vector, i*i);
        printf("Vector count: %zu\n", vector_get_count(vector));
    }

    printf("\nNext pointer: %zu\n", vector_get_next_pointer(vector));

    vector_push_back(vector, 2);
    vector_push_back(vector, 3);
    vector_push_back(vector, 4);

    vector_pop_back(vector);
    vector_pop_back(vector);

    struct vector* additional = vector_create(capacity);

    for (size_t i = 1; i <= capacity * 3; i++) {
        vector_push_back(additional, - i * i);
    }

    vector_concatenate(vector, additional);

    return;
}