#include "../../cstd_deque.h"

int main() {
    // create an empty deque of integers
    deque_t dq;
    cstd_deque_init(&dq, sizeof(int));

    // add some elements to the front and back of the deque
    int value1 = 10;
    cstd_deque_push_back(&dq, &value1);
    int value2 = 20;
    cstd_deque_push_front(&dq, &value2);
    int value3 = 30;
    cstd_deque_push_back(&dq, &value3);

    // print the size of the deque
    printf("Size of deque: %zu\n", cstd_deque_size(&dq));

    // print the first element of the deque
    int* first = (int*)cstd_deque_front(&dq);
    printf("First element: %d\n", *first);

    // print the last element of the deque
    int* last = (int*)cstd_deque_back(&dq);
    printf("Last element: %d\n", *last);

    // change the value of the second element
    int* second = (int*)cstd_deque_at(&dq, 1);
    *second = 40;

    // print all the elements of the deque
    printf("All elements: ");
    for (size_t i = 0; i < cstd_deque_size(&dq); i++) {
        int* element = (int*)cstd_deque_at(&dq, i);
        printf("%d ", *element);
    }
    printf("\n");

    // remove the first and last elements from the deque
    cstd_deque_pop_front(&dq);
    cstd_deque_pop_back(&dq);

    // print the size of the deque again
    printf("Size of deque after pop_front() and pop_back(): %zu\n", cstd_deque_size(&dq));

    // clear the deque
    cstd_deque_clear(&dq);

    // print the size of the deque after clear()
    printf("Size of deque after clear(): %zu\n", cstd_deque_size(&dq));

    // free the deque memory
    cstd_deque_free(&dq);

    return 0;
}
