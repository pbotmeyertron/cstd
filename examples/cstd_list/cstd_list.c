#include "../../cstd_list.h"

int main() {
    // Create a list of integers
    list_t numbers;
    cstd_list_init(&numbers, sizeof(int));

    // Add elements to the list (push_back inserts elements at the end)
    int values[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        cstd_list_push_back(&numbers, &values[i]);
    }

    // Insert an element in the middle of the list
    int new_val = 25;
    cstd_list_insert(&numbers, 2, &new_val);

    // Remove an element from the list (erase removes elements by index)
    int index_to_remove = -1;
    for (size_t i = 0; i < cstd_list_size(&numbers); i++) {
        int* current_value = (int*)cstd_list_at(&numbers, i);
        if (*current_value == 20) {
            index_to_remove = i;
            break;
        }
    }

    if (index_to_remove >= 0) {
        cstd_list_erase(&numbers, index_to_remove);
    }

    // Iterate and print elements in the list
    for (size_t i = 0; i < cstd_list_size(&numbers); i++) {
        int* current_value = (int*)cstd_list_at(&numbers, i);
        printf("%d ", *current_value);
    }

    printf("\n");

    // Free the list
    cstd_list_free(&numbers);

    return 0;
}
