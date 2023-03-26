#include "../../cstd_multiset.h"

int compare_int(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return int_a - int_b;
}

void print_multiset_inorder(const multiset_t* set, bst_node_t* node) {
    if (node == NULL) {
        return;
    }
    print_multiset_inorder(set, node->left);
    int value = *(int*)cstd_multiset_data(node);
    unsigned int count = cstd_multiset_count(node);
    for (unsigned int i = 0; i < count; ++i) {
        printf("%d ", value);
    }
    print_multiset_inorder(set, node->right);
}

int main() {
    multiset_t num_multiset;
    cstd_multiset_init(&num_multiset, sizeof(int), compare_int);

    int numbers[] = {5, 3, 7, 5, 1};
    size_t num_elements = sizeof(numbers) / sizeof(numbers[0]);

    for (size_t i = 0; i < num_elements; ++i) {
        cstd_multiset_insert(&num_multiset, &numbers[i]);
    }

    printf("Contents of the multiset: ");
    print_multiset_inorder(&num_multiset, num_multiset.root);
    printf("\n");

    int target = 5;
    bst_node_t* found_node = cstd_multiset_find(&num_multiset, &target);
    unsigned int count = found_node ? cstd_multiset_count(found_node) : 0;
    printf("Count of %d in the multiset: %u\n", target, count);

    int to_erase = 3;
    cstd_multiset_remove(&num_multiset, &to_erase);

    printf("Contents of the multiset after erasing %d: ", to_erase);
    print_multiset_inorder(&num_multiset, num_multiset.root);
    printf("\n");

    cstd_multiset_free(&num_multiset);

    return 0;
}
