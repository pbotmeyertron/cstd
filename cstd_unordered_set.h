#pragma once

#include "cstd_common.h"

#define CSTD_UNORDERED_SET_INIT_BUCKET_COUNT 16
#define CSTD_UNORDERED_SET_MAX_LOAD_FACTOR 0.75

typedef struct hash_node {
    void*             key;
    struct hash_node* next;
} hash_node_t;

typedef size_t  (*hash_func_t)(const void* key);
typedef int32_t (*compare_func_t)(const void* a, const void* b);

/* 
 * Unordered set data structure. It stores data in a contiguous block
 * of memory. It has a dynamic size, which can be changed by adding or
 * removing elements.
 */
typedef struct {
    hash_node_t**  buckets;
    size_t         size;
    size_t         bucket_count;
    size_t         key_size;
    hash_func_t    hash;
    compare_func_t compare;
} unordered_set_t;

cstd_inline hash_node_t* 
new_hash_node(const void* key, size_t key_size) {
    hash_node_t* node = (hash_node_t*)malloc(sizeof(hash_node_t));
    node->key = malloc(key_size);
    memcpy(node->key, key, key_size);
    node->next = NULL;
    return node;
}

cstd_inline void 
free_hash_node(hash_node_t* node) {
    free(node->key);
    free(node);
}

/* 
 * Initialize an unordered set with the given key size, hash function,
 * and compare function.
 */
cstd_inline void 
cstd_unordered_set_init(unordered_set_t* set,
                        size_t key_size, hash_func_t hash,
                        compare_func_t compare) {
    set->buckets = (hash_node_t**)calloc(CSTD_UNORDERED_SET_INIT_BUCKET_COUNT,
                                         sizeof(hash_node_t*));
    set->size = 0;
    set->bucket_count = CSTD_UNORDERED_SET_INIT_BUCKET_COUNT;
    set->key_size = key_size;
    set->hash = hash;
    set->compare = compare;
}

cstd_inline void 
cstd_unordered_set_free(unordered_set_t* set) {
    for (size_t i = 0; i < set->bucket_count; i++) {
        hash_node_t* node = set->buckets[i];
        while (node) {
            hash_node_t* next = node->next;
            free_hash_node(node);
            node = next;
        }
    }
    free(set->buckets);
}

/* 
 * Resizes the unordered set to twice the size of the current capacity.
 */
cstd_inline void 
cstd_unordered_set_resize(unordered_set_t* set,
                          size_t new_bucket_count) {
    hash_node_t** new_buckets =
        (hash_node_t**)calloc(new_bucket_count, sizeof(hash_node_t*));

    for (size_t i = 0; i < set->bucket_count; i++) {
        hash_node_t* node = set->buckets[i];
        while (node) {
            hash_node_t* next = node->next;
            size_t new_bucket_index = set->hash(node->key) % new_bucket_count;

            node->next = new_buckets[new_bucket_index];
            new_buckets[new_bucket_index] = node;

            node = next;
        }
    }

    free(set->buckets);
    set->buckets = new_buckets;
    set->bucket_count = new_bucket_count;
}

/* 
 * Returns true if the key was inserted, false if it already exists.
 */
cstd_inline bool 
cstd_unordered_set_insert(unordered_set_t* set,
                          const void* key) {
    if (set->size + 1 >
        set->bucket_count * CSTD_UNORDERED_SET_MAX_LOAD_FACTOR) {
        cstd_unordered_set_resize(set, set->bucket_count * 2);
    }

    size_t bucket_index = set->hash(key) % set->bucket_count;
    hash_node_t* node = set->buckets[bucket_index];

    while (node) {
        if (set->compare(node->key, key) == 0) {
            return false;  // Key already exists in the set
        }
        node = node->next;
    }

    hash_node_t* new_node = new_hash_node(key, set->key_size);
    new_node->next = set->buckets[bucket_index];
    set->buckets[bucket_index] = new_node;
    set->size++;
    return true;
}

/*
 * Returns true if the key was found and removed, false otherwise.
 */
cstd_inline bool 
cstd_unordered_set_erase(unordered_set_t* set,
                                          const void* key) {
    size_t bucket_index = set->hash(key) % set->bucket_count;
    hash_node_t* node = set->buckets[bucket_index];
    hash_node_t* prev = NULL;

    while (node) {
        if (set->compare(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                set->buckets[bucket_index] = node->next;
            }
            free_hash_node(node);
            set->size--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

/*
 * Returns true if the key was found, false otherwise.
 */
cstd_inline bool 
cstd_unordered_set_find(const unordered_set_t* set,
                        const void* key) {
    size_t bucket_index = set->hash(key) % set->bucket_count;
    hash_node_t* node = set->buckets[bucket_index];

    while (node) {
        if (set->compare(node->key, key) == 0) {
            return true;
        }
        node = node->next;
    }
    return false;
}

/*
 * Returns the number of elements in the set.
 */
cstd_inline size_t 
cstd_unordered_set_size(const unordered_set_t* set) {
    return set->size;
}

/*
 * Returns true if the set is empty, false otherwise.
 */
cstd_inline bool 
cstd_unordered_set_empty(const unordered_set_t* set) {
    return set->size == 0;
}
