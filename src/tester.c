#include "../include/tester.h"

#include <stdio.h>
#include <stdlib.h>

void vector_test() {
    vector_test_add_delete();
    vector_test_push_pop();
    vector_test_concatenate();
    vector_test_sort();
}

void vector_test_add_delete() {
    printf("\n\nStarting add-delete test...\n\n");
    struct vector* vector = vector_create(0);
    for (size_t i = 0; i < 16; i++) {
        vector_push_back(vector, -i);
    }
    vector_delete_value(vector, 0);
    vector_delete_value(vector, 9);
    vector_print(vector, "test_add_delete.txt");
    printf("Current amount of defined elements: %zu\n", vector_get_count(vector));
    vector_destroy(vector);
}

void vector_test_sort() {
    printf("\n\nStarting sort test...\n\n");
    struct vector* vector = vector_create(10);

    size_t size = vector_get_size(vector) * 2;

    for (size_t i = 1; i <= size * 4; i += 2) {
        vector_set_value(vector, i, rand() % 75);
    }
    vector_show(vector);
    vector_sort(vector);
    printf("\nSorted vector:\n\n");
    // vector_show(vector);
    vector_show_defined(vector);
    vector_print(vector, "test_sort.txt");

    vector_destroy(vector);
}

void vector_test_push_pop() {

    printf("\n\nStarting push-pop test...\n\n");

    size_t capacity = 0;
    struct vector* vector = vector_create(capacity);

    int64_t value;
    for (size_t i = 0; i < 15; ++i) {
        vector_push_back(vector, i * i);
        printf("Pushed %zu\n", i * i);

        vector_push_back(vector, i * i * i);
        printf("Pushed %zu\n", i * i * i);

        value = vector_pop_back(vector);
        printf("Popped %zu\n", value);
    }

    vector_print(vector, "test_push_pop.txt");

    vector_destroy(vector);
}

void vector_test_concatenate() {
    printf("\n\nStarting concatenate test...\n\n");
    struct vector* vector1 = vector_create(10);
    struct vector* vector2 = vector_create(10);

    for (size_t i = 0; i < 10; ++i) {
        vector_set_value(vector1, i, i * i);
        vector_set_value(vector2, i, - i * i * i);
    }

    vector_concatenate(vector1, vector2);

    vector_print(vector1, "test_concatenate.txt");

    vector_destroy(vector1);
    vector_destroy(vector2);
}