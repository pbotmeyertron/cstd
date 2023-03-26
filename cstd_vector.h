#pragma once

#include "cstd_common.h"

#define VECTOR_INIT_CAPACITY 16

/* 
 * Dynamic array data structure. It stores data in a contiguous block
 * of memory. It has a dynamic size, which can be changed by adding or
 * removing elements.
 */
typedef struct {
    void*  data;
    size_t size;
    size_t capacity;
    size_t element_size;
} vector_t;

/*
 * Initialize a vector with the given element size.
 */
cstd_inline void 
cstd_vector_init(vector_t* vec, const size_t element_size) {
    vec->data = malloc(VECTOR_INIT_CAPACITY * element_size);
    if (vec->data) {
        vec->size = 0;
        vec->capacity = VECTOR_INIT_CAPACITY;
        vec->element_size = element_size;
    } else {
        vec->size = 0;
        vec->capacity = 0;
        vec->element_size = element_size;
    }
}

/*
 * Free the memory used by a vector. This does not free any memory
 * allocated for the elements in the vector.
 */
cstd_inline void 
cstd_vector_free(vector_t* vec) {
    if (vec->data) {
        free(vec->data);
    }
}

/* 
 * Resizes the vector to 1.5 times the size of the current capacity.
 */
cstd_inline void
cstd_vector_resize(vector_t* vec) {
    size_t old_capacity = vec->capacity;
    vec->capacity = vec->capacity * 3 / 2;
    void* new_data = realloc(vec->data, vec->capacity * vec->element_size);
    if (new_data) {
        vec->data = new_data;
    } else {
        vec->capacity = old_capacity;
    }
}


/*
 * This function reserves space in the vector so that it can hold
 * new_capacity elements. If the new capacity is smaller than the
 * current capacity, then this function does nothing.
*/
cstd_inline void 
cstd_vector_reserve(vector_t* vec, const size_t new_capacity) {
    if (new_capacity > vec->capacity) {
        vec->capacity = new_capacity;
        void* new_data = realloc(vec->data, vec->capacity * vec->element_size);
        if (new_data) {
            vec->data = new_data;
        } else {
            vec->capacity = vec->size;
        }
    }
}

/* 
 * This function shrinks the capacity of the vector to the size of the vector.
 * If the capacity is already the same as the size, nothing is done. 
 */
cstd_inline void 
cstd_vector_shrink_to_fit(vector_t* vec) {
    if (vec->size < vec->capacity) {
        vec->capacity = vec->size;
        void* new_data = realloc(vec->data, vec->capacity * vec->element_size);
        if (new_data) {
            vec->data = new_data;
        }
    }
}

/*
* This function pushes an element onto the end of the vector.
* The element is copied into the vector, and the vector's size
* is incremented. The vector is resized if it is full.
*/
cstd_inline void 
cstd_vector_push_back(vector_t* vec, void* element) {
    if (vec->size == vec->capacity) {
        cstd_vector_resize(vec);
    }
    memcpy((char*)vec->data +
                  vec->size * 
                  vec->element_size, 
                  element, 
                  vec->element_size);
    vec->size++;
}

/* 
 * Removes the last element from a vector. If the vector is 
 * empty, this function does nothing.
 */
cstd_inline void 
cstd_vector_pop_back(vector_t* vec) {
    if (vec->size > 0) {
        vec->size--;
    }
}

/*
 * Returns a pointer to the element at the specified index, or NULL if the index
 * is out of bounds.
 */
cstd_inline void* 
cstd_vector_at(vector_t* vec, const size_t index) {
    if (index >= vec->size) {
        return NULL;
    } else {
        return (char*)vec->data + index * vec->element_size;
    }
}

/* 
 *  Clears a vector by setting the size to zero.
 *  This does not free the memory of the vector.
 */
cstd_inline void 
cstd_vector_clear(vector_t* vec) {
    vec->size = 0;
}

/*
 * Returns true if the vector is empty, false otherwise.
 */
cstd_inline bool 
cstd_vector_empty(vector_t* vec) {
    return vec->size == 0;
}

/*
 * Inserts the given element into the vector at the given index. If the
 * vector is already full, it is resized before the element is inserted.
 * The element size is given in the vector struct, so there is no need
 * to pass the size as a parameter.
 */
cstd_inline void 
cstd_vector_insert(vector_t* vec, const size_t index, void* element) {
    assert(index <= vec->size);
    if (vec->size == vec->capacity) {
        cstd_vector_resize(vec);
    }
    memmove((char*)vec->data + (index + 1) * vec->element_size,
            (char*)vec->data + index * vec->element_size,
            (vec->size - index) * vec->element_size);
    memcpy((char*)vec->data + 
                  index     * 
                  vec->element_size, 
                  element, 
                  vec->element_size);
    vec->size++;
}

/* 
 * Erases the element at the given index in the vector. 
 */
cstd_inline void 
cstd_vector_erase(vector_t* vec, const size_t index) {
    assert(index < vec->size);
    memmove((char*)vec->data + index * vec->element_size,
            (char*)vec->data + (index + 1) * vec->element_size,
            (vec->size - index - 1) * vec->element_size);
    vec->size--;
}

/*
 * Returns the number of elements in the specified vector.
 */
cstd_inline size_t 
cstd_vector_size(vector_t* vec) {
    return vec->size;
}

/* 
 * Returns the capacity of the vector `vec`. The capacity is the
 * number of elements that the vector can hold without needing to
 * resize.
 */
cstd_inline size_t 
cstd_vector_capacity(vector_t* vec) {
    return vec->capacity;
}
