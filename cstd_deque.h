#pragma once

#include "cstd_common.h"

#define DEQUE_INIT_CAPACITY 16

/*
 * A deque is a double-ended queue. It is a data structure that allows for
 * efficient insertion and removal of elements from both ends.
 */
typedef struct {
    /* A pointer to the underlying data buffer */
    void*  data;
    /* The index of the head element */
    size_t head;
    /* The index of the tail element */
    size_t tail;
    /* The number of elements in the deque */
    size_t size;
    /* The maximum number of elements in the deque */
    size_t capacity;
    /* The size of each element in the deque */
    size_t element_size;
} deque_t;

/*
 * Allocate memory for the deque's data and initialize the head and
 * tail indices to 0. The size is 0 and the capacity is set to the
 * initial capacity. The element size is set to the given element
 * size.
 */
cstd_inline void 
cstd_deque_init(deque_t* dq, const size_t element_size) {
    if (dq == NULL) {
        return;
    }
    dq->data = malloc(DEQUE_INIT_CAPACITY * element_size);
    if (dq->data == NULL) {
        return;
    }
    dq->head = 0;
    dq->tail = 0;
    dq->size = 0;
    dq->capacity = DEQUE_INIT_CAPACITY;
    dq->element_size = element_size;
}

/*
 * Resizes the deque's backing array to the specified capacity. This
 * function should only be called by the cstd_deque_push_back and
 * cstd_deque_push_front functions when the deque is full. 
 */
cstd_inline void 
cstd_deque_resize(deque_t* dq, const size_t new_capacity) {
    if (dq->data) {
        void* new_data = malloc(new_capacity * dq->element_size);
        if (new_data) {
            for (size_t i = 0; i < dq->size; i++) {
                memmove((char*)new_data + i * dq->element_size,
                        (char*)dq->data + 
                             ((dq->head + i) % dq->capacity) * 
                                               dq->element_size,
                        dq->element_size);
            }
            free(dq->data);
            dq->data = new_data;
            dq->head = 0;
            dq->tail = dq->size;
            dq->capacity = new_capacity;
        }
    }
}

cstd_inline void 
cstd_deque_free(deque_t* dq) { 
    if (dq->data) { 
        free(dq->data); 
    } 
}

/* 
 * This function pushes an element to the back of the deque. If the deque is
 * full, the capacity is doubled. 
*/
cstd_inline void 
cstd_deque_push_back(deque_t* dq, void* element) {
    if (dq->size == dq->capacity) {
        cstd_deque_resize(dq, dq->capacity * 2);
    }
    memcpy((char*)dq->data + dq->tail * dq->element_size, element,
           dq->element_size);
    dq->tail = (dq->tail + 1) % dq->capacity;
    dq->size++;
}

/* Pushes an element to the front of the deque.
 * If the deque is full, the deque is resized to the next power of 2.
 * The element is copied to the deque using memcpy. 
 */
cstd_inline void
cstd_deque_push_front(deque_t* dq, void* element) {
    if (dq->size == dq->capacity) {
        cstd_deque_resize(dq, dq->capacity * 2);
    }
    dq->head = (dq->head + dq->capacity - 1) % dq->capacity;
    memcpy((char*)dq->data + dq->head * dq->element_size, element,
           dq->element_size);
    dq->size++;
}

/* 
 * This function removes the last element of a deque, decrementing the
 * size of the deque by 1. If the deque is empty, this function has no
 * effect.
 */
cstd_inline void 
cstd_deque_pop_back(deque_t* dq) {
    if (dq->size > 0) {
        dq->tail = (dq->tail + dq->capacity - 1) % dq->capacity;
        dq->size--;
    }
}

/* 
 * This function is used to remove the first element of a deque.
 * Pops the first element of the deque by moving the head pointer
 * along one position, and decreasing the size of the deque by one.
 */
cstd_inline void 
cstd_deque_pop_front(deque_t* dq) {
    if (dq->size > 0) {
        dq->head = (dq->head + 1) % dq->capacity;
        dq->size--;
    }
}

/* 
 * Returns a pointer to the element at the given index in the deque.
 * The index must be in the range [0, dq->size).
 */
cstd_inline void* 
cstd_deque_at(deque_t* dq, const size_t index) {
    if (index >= dq->size) {
        return NULL;
    }
    return (char*)dq->data + 
                ((dq->head + index) % 
                  dq->capacity) * dq->element_size;
}

/*
 * Returns a pointer to the first element in the deque.
 * The deque must not be empty.
 */
cstd_inline void* 
cstd_deque_front(deque_t* dq) {
    assert(dq->size > 0);
    return (char*)dq->data + dq->head * dq->element_size;
}

/* 
 * Return a pointer to the last element of the deque.
 */
cstd_inline void* 
cstd_deque_back(deque_t* dq) {
    assert(dq->size > 0);
    return (char*)dq->data +
           ((dq->tail + dq->capacity - 1) % dq->capacity) * dq->element_size;
}

/*
 * Returns true if the deque is empty, false otherwise. 
 */
cstd_inline bool 
cstd_deque_empty(deque_t* dq) { 
    return dq->size == 0; 
}


/* 
 * Returns the size of the given deque. 
 */ 
cstd_inline size_t 
cstd_deque_size(deque_t* dq) { 
    return dq->size; 
}

/* 
 * Clears the deque pointed to by dq
 */
cstd_inline void 
cstd_deque_clear(deque_t* dq) {
    dq->head = 0;
    dq->tail = 0;
    dq->size = 0;
}

/* 
 * Shrinks the capacity of the deque to fit the number of elements it contains.
 * This function does nothing if the deque is already at its minimum capacity.
 */
cstd_inline void 
cstd_deque_shrink_to_fit(deque_t* dq) {
    if (dq->capacity > DEQUE_INIT_CAPACITY && dq->size < dq->capacity / 2) {
        cstd_deque_resize(dq, dq->size ? dq->size : DEQUE_INIT_CAPACITY);
    }
}