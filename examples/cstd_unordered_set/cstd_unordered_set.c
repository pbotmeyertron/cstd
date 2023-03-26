#include "../../cstd_unordered_set.h"

size_t string_hash(const void* key) {
    const char* str = (const char*)key;
    size_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

int main() {
    // Initialize the unordered_set for strings
    cstd_unordered_set_t name_set;
    cstd_unordered_set_init(&name_set, sizeof(char*), string_hash, string_compare);

    // Insert elements into the set
    cstd_unordered_set_insert(&name_set, "Alice");
    cstd_unordered_set_insert(&name_set, "Bob");
    cstd_unordered_set_insert(&name_set, "Carol");

    // Check if an element exists in the set
    const char* name = "Alice";
    if (cstd_unordered_set_find(&name_set, name)) {
        printf("%s found in the set.\n", name);
    } else {
        printf("%s not found in the set.\n", name);
    }

    // Iterate through the set and print the elements
    for (size_t i = 0; i < name_set.bucket_count; i++) {
        hash_node_t* node = name_set.buckets[i];
        while (node) {
            printf("%s\n", (char*)node->key);
            node = node->next;
        }
    }

    // Free the resources used by the unordered_set
    cstd_unordered_set_free(&name_set);
    return 0;
}
