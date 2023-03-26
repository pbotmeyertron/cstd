#include "../../cstd_vector.h"

int main() {
    // create an empty vector of integers
    vector_t vec;
    cstd_vector_init(&vec, sizeof(int));

    // add some elements to the vector
    int value1 = 10;
    cstd_vector_push_back(&vec, &value1);
    int value2 = 20;
    cstd_vector_push_back(&vec, &value2);
    int value3 = 30;
    cstd_vector_push_back(&vec, &value3);

    // print the size of the vector
    printf("Size of vector: %zu\n", vector_size(&vec));

    // print the first element of the vector
    int* first = (int*)vector_at(&vec, 0);
    printf("First element: %d\n", *first);

    // print the last element of the vector
    int* last = (int*)vector_at(&vec, vector_size(&vec)-1);
    printf("Last element: %d\n", *last);

    // change the value of the second element
    int* second = (int*)vector_at(&vec, 1);
    *second = 40;

    // print all the elements of the vector
    printf("All elements: ");
    for (size_t i = 0; i < vector_size(&vec); i++) {
        int* element = (int*)vector_at(&vec, i);
        printf("%d ", *element);
    }
    printf("\n");

    // remove the last element from the vector
    cstd_vector_pop_back(&vec);

    // print the size of the vector again
    printf("Size of vector after pop_back(): %zu\n", vector_size(&vec));

    // clear the vector
    cstd_vector_clear(&vec);

    // print the size of the vector after clear()
    printf("Size of vector after clear(): %zu\n", vector_size(&vec));

    // free the vector memory
    cstd_vector_free(&vec);

    return 0;
}
