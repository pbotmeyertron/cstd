#pragma once

#include "cstd_common.h"

// Define an initial capacity for the hash table
#define UNORDERED_MAP_INIT_CAPACITY 16

/* Define a load factor threshold for resizing */
#define UNORDERED_MAP_MAX_LOAD_FACTOR 0.75

// Define a generic key-value pair
typedef struct key_value_pair_t {
    void*                    key;
    void*                    value;
    struct key_value_pair_t* next;
} key_value_pair_t;

typedef struct {
    key_value_pair_t** buckets;
    size_t             size;
    size_t             capacity;
    size_t             key_size;
    size_t             value_size;
    uint32_t (*hash_function)(const void *key);
    bool     (*key_equals)(const void *key1, const void *key2);
} unordered_map_t;

/* Resize the hash table, rehashing all key-value pairs */
cstd_inline void 
cstd_unordered_map_resize_and_rehash(unordered_map_t* map, 
                                     const size_t new_capacity) {
    key_value_pair_t **new_buckets =
        (key_value_pair_t**)calloc(new_capacity, sizeof(key_value_pair_t*));
    for (size_t i = 0; i < map->capacity; ++i) {
        key_value_pair_t *pair = map->buckets[i];
        while (pair) {
            key_value_pair_t *next = pair->next;
            unsigned int hash = map->hash_function(pair->key);
            size_t index = hash % new_capacity;
            pair->next = new_buckets[index];
            new_buckets[index] = pair;
            pair = next;
        }
    }
    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
}

cstd_inline void 
cstd_unordered_map_init(
    unordered_map_t *map, const size_t key_size, const size_t value_size,
    uint32_t (*hash_function)(const void *key),
    bool (*key_equals)(const void *key1, const void *key2)) {
    map->buckets = (key_value_pair_t**)calloc(UNORDERED_MAP_INIT_CAPACITY,
                                             sizeof(key_value_pair_t*));
    map->size = 0;
    map->capacity = UNORDERED_MAP_INIT_CAPACITY;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_function = hash_function;
    map->key_equals = key_equals;
}

cstd_inline void 
cstd_unordered_map_free(unordered_map_t *map) {
    if (map->buckets) {
        for (size_t i = 0; i < map->capacity; i++) {
            key_value_pair_t *pair = map->buckets[i];
            while (pair) {
                key_value_pair_t *next = pair->next;
                free(pair->key);
                free(pair->value);
                free(pair);
                pair = next;
            }
        }
        free(map->buckets);
    }
}

cstd_inline void*
cstd_unordered_map_find(unordered_map_t *map,
                        const void *key) {
    unsigned int hash = map->hash_function(key);
    size_t index = hash % map->capacity;
    key_value_pair_t *pair = map->buckets[index];
    while (pair) {
        if (map->key_equals(pair->key, key)) {
            return pair->value;
        }
        pair = pair->next;
    }
    return NULL;
}

cstd_inline void 
cstd_unordered_map_insert(unordered_map_t *map,
                          const void *key, 
                          const void *value) {
    if (map->size >= map->capacity * UNORDERED_MAP_MAX_LOAD_FACTOR) {
        size_t new_capacity = map->capacity * 2;
        cstd_unordered_map_resize_and_rehash(map, new_capacity);
    }

    unsigned int hash = map->hash_function(key);
    size_t index = hash % map->capacity;
    key_value_pair_t *pair = map->buckets[index];
    while (pair) {
        if (map->key_equals(pair->key, key)) {
            memcpy(pair->value, value, map->value_size);
            return;
        }
        pair = pair->next;
    }
    pair = (key_value_pair_t *)malloc(sizeof(key_value_pair_t));
    pair->key = malloc(map->key_size);
    memcpy(pair->key, key, map->key_size);
    pair->value = malloc(map->value_size);
    memcpy(pair->value, value, map->value_size);
    pair->next = map->buckets[index];
    map->buckets[index] = pair;
    map->size++;
}

cstd_inline void 
cstd_unordered_map_insert_with_resize(unordered_map_t *map,
                                      const void *key,
                                      const void *value) {
    // Check if resizing is needed
    if (map->size >= map->capacity * UNORDERED_MAP_MAX_LOAD_FACTOR) {
        size_t new_capacity = map->capacity * 2;
        cstd_unordered_map_resize_and_rehash(map, new_capacity);
    }

    // Proceed with the insertion
    cstd_unordered_map_insert(map, key, value);
}

cstd_inline void 
cstd_unordered_map_erase(unordered_map_t *map,
                         const void *key) {
    unsigned int hash = map->hash_function(key);
    size_t index = hash % map->capacity;

    key_value_pair_t *pair = map->buckets[index];
    key_value_pair_t *prev = NULL;

    while (pair) {
        if (map->key_equals(pair->key, key)) {
            if (prev) {
                prev->next = pair->next;
            } else {
                map->buckets[index] = pair->next;
            }

            free(pair->key);
            free(pair->value);
            free(pair);
            map->size--;
            return;
        }
        prev = pair;
        pair = pair->next;
    }
}

cstd_inline bool 
cstd_unordered_map_empty(unordered_map_t *map) {
    return map->size == 0;
}

cstd_inline size_t 
cstd_unordered_map_size(unordered_map_t *map) {
    return map->size;
}

cstd_inline void 
cstd_unordered_map_clear(unordered_map_t *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        key_value_pair_t *pair = map->buckets[i];
        while (pair) {
            key_value_pair_t *next = pair->next;
            free(pair->key);
            free(pair->value);
            free(pair);
            pair = next;
        }
        map->buckets[i] = NULL;
    }
    map->size = 0;
}
