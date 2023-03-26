#include "../../cstd_map.h"

int32_t string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

void print_map(map_t* map) {
    for (node_t* node = map->root; node != NULL; node = node->right) {
        printf("%s: %d\n", (char*)node->key, *(int*)node->value);
    }
}

int main() {
    map_t age_map;
    cstd_map_init(&age_map, sizeof(char*), sizeof(int), string_compare);

    // Add key-value pairs to the map
    char* alice_key = "Alice";
    int alice_value = 30;
    cstd_map_insert(&age_map, alice_key, &alice_value);

    char* bob_key = "Bob";
    int bob_value = 25;
    cstd_map_insert(&age_map, bob_key, &bob_value);

    char* charlie_key = "Charlie";
    int charlie_value = 35;
    cstd_map_insert(&age_map, charlie_key, &charlie_value);

    // Access and modify values using the key
    alice_value = 31;
    cstd_map_insert(&age_map, alice_key, &alice_value);

    // Check if a key is present in the map
    char* eve_key = "Eve";
    if (!cstd_map_find(&age_map, eve_key)) {
        printf("Eve is not in the map\n");
    }

    // Iterate and print key-value pairs in the map
    print_map(&age_map);

    // Remove an element from the map
    cstd_map_delete(&age_map, bob_key);

    // Print the map size
    printf("Map size: %zu\n", cstd_map_size(&age_map));

    // Free the map memory
    cstd_map_free(&age_map);

    return 0;
}
