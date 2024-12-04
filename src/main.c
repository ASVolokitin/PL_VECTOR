
#include <stdio.h>

#include "../include/vector.h"
#include "../include/tester.h"

int main(void) {
    size_t capacity = 3;
    struct vector* vector = vector_create(capacity);

    vector_test(vector);
    vector_print(vector, "output.txt");
    vector_destroy(vector);
    return 0;
}