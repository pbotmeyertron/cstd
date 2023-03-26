#include <stdio.h>
#include "../../cstd_vector.h"

/* Example of using the cstd_vector_t type to store int elements */

int main() {
    vector_t int_vector;

    // Initialize the vector to hold int elements
    cstd_vector_init(&int_vector, sizeof(int));

    // Add elements to the vector
    int values[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < sizeof(values) / sizeof(int); i++) {
        cstd_vector_push_back(&int_vector, &values[i]);
    }

    // Access elements and print the vector
    printf("Vector elements: ");
    for (size_t i = 0; i < cstd_vector_size(&int_vector); i++) {
        int* element = (int*)cstd_vector_at(&int_vector, i);
        if (element) {
            printf("%d ", *element);
        }
    }
    printf("\n");

    // Remove the last element
    cstd_vector_pop_back(&int_vector);

    // Insert an element at index 2
    int value_to_insert = 6;
    cstd_vector_insert(&int_vector, 2, &value_to_insert);

    // Erase the element at index 1
    cstd_vector_erase(&int_vector, 1);

    // Print the modified vector
    printf("Modified vector elements: ");
    for (size_t i = 0; i < cstd_vector_size(&int_vector); i++) {
        int* element = (int*)cstd_vector_at(&int_vector, i);
        if (element) {
            printf("%d ", *element);
        }
    }
    printf("\n");

    // Free the vector memory
    cstd_vector_free(&int_vector);

    return 0;
}
