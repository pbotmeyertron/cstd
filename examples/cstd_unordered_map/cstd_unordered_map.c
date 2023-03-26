#include "../../cstd_unordered_map.h"

// Custom hash function for strings
uint32_t string_hash_function(const void *key) {
    const char *str = (const char *)key;
    uint32_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// Custom key comparison function for strings
bool string_key_equals(const void *key1, const void *key2) {
    return strcmp((const char *)key1, (const char *)key2) == 0;
}

int main() {
    // Create an unordered_map with key type string and value type int
    unordered_map_t age_map;
    cstd_unordered_map_init(&age_map, sizeof(char *), sizeof(int), string_hash_function, string_key_equals);

    // Insert key-value pairs into the map
    const char *alice = "Alice";
    int alice_age = 30;
    cstd_unordered_map_insert(&age_map, alice, &alice_age);

    const char *bob = "Bob";
    int bob_age = 25;
    cstd_unordered_map_insert(&age_map, bob, &bob_age);

    const char *carol = "Carol";
    int carol_age = 35;
    cstd_unordered_map_insert(&age_map, carol, &carol_age);

    // Find a value by key
    const char *key = "Alice";
    int *age = (int *)cstd_unordered_map_find(&age_map, key);

    if (age) {
        printf("Age of %s is: %d\n", key, *age);
    } else {
        printf("%s not found in the map.\n", key);
    }

    // Iterate through the map and print key-value pairs
    for (size_t i = 0; i < age_map.capacity; ++i) {
        key_value_pair_t *pair = age_map.buckets[i];
        while (pair) {
            printf("%s: %d\n", (const char *)pair->key, *(int *)pair->value);
            pair = pair->next;
        }
    }

    // Free the resources
    cstd_unordered_map_free(&age_map);

    return 0;
}
