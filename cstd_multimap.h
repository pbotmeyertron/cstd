#pragma once

#include "cstd_vector.h"

#define MULTIMAP_INIT_CAPACITY 16

typedef struct {
    void* key;
    vector_t value;
} multimap_entry_t;

typedef struct {
    multimap_entry_t* data;
    size_t            size;
    size_t            capacity;
    size_t            key_size;
    size_t            value_element_size;
    int32_t (*key_cmp)(const void*, const void*);
} multimap_t;

cstd_inline void 
cstd_multimap_init(multimap_t* mmap, 
                   const size_t key_size,
                   const size_t value_element_size,
                   int32_t (*key_cmp)(const void*, const void*)) {
    mmap->data = 
        (multimap_entry_t*)malloc(MULTIMAP_INIT_CAPACITY * 
                sizeof(multimap_entry_t));
    mmap->size = 0;
    mmap->capacity = MULTIMAP_INIT_CAPACITY;
    mmap->key_size = key_size;
    mmap->value_element_size = value_element_size;
    mmap->key_cmp = key_cmp;
}

cstd_inline void 
cstd_multimap_free(multimap_t* mmap) {
    for (size_t i = 0; i < mmap->size; i++) {
        cstd_vector_free(&(mmap->data[i].value));
    }
    free(mmap->data);
}

cstd_inline void 
cstd_multimap_resize(multimap_t* mmap) {
    mmap->capacity *= 2;
    mmap->data = (multimap_entry_t*)realloc(
        mmap->data, mmap->capacity * sizeof(multimap_entry_t));
}

cstd_inline multimap_entry_t* 
cstd_multimap_find_or_insert(multimap_t* mmap, void* key) {
    for (size_t i = 0; i < mmap->size; i++) {
        if (mmap->key_cmp(mmap->data[i].key, key) == 0) {
            return &(mmap->data[i]);
        }
    }
    if (mmap->size == mmap->capacity) {
        cstd_multimap_resize(mmap);
    }
    mmap->data[mmap->size].key = malloc(mmap->key_size);
    memcpy(mmap->data[mmap->size].key, key, mmap->key_size);
    cstd_vector_init(&(mmap->data[mmap->size].value), 
                       mmap->value_element_size);
    mmap->size++;
    return &(mmap->data[mmap->size - 1]);
}

cstd_inline void 
cstd_multimap_insert(multimap_t* mmap, void* key,
                                       void* value) {
    multimap_entry_t* entry = cstd_multimap_find_or_insert(mmap, key);
    cstd_vector_push_back(&(entry->value), value);
}

cstd_inline vector_t* 
cstd_multimap_get(multimap_t* mmap, void* key) {
    for (size_t i = 0; i < mmap->size; i++) {
        if (mmap->key_cmp(mmap->data[i].key, key) == 0) {
            return &(mmap->data[i].value);
        }
    }
    return NULL;
}

cstd_inline bool 
cstd_multimap_empty(multimap_t* mmap) {
    return mmap->size == 0;
}

cstd_inline size_t 
cstd_multimap_size(multimap_t* mmap) { 
    return mmap->size; 
}

cstd_inline size_t 
cstd_multimap_capacity(multimap_t* mmap) {
    return mmap->capacity;
}
