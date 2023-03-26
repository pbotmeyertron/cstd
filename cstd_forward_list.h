#pragma once

#include "cstd_common.h"

typedef struct forward_list_node {
    void*                     data;
    struct forward_list_node* next;
} forward_list_node_t;

/* 
 * This is a forward list implementation. The implementation uses a
 * forward_list_node_t struct as the list node, which contains a pointer
 * to the next node in the list, and a void* pointer to the data. The
 * forward_list_t struct contains the head of the list, and the size of
 * the data in the list. 
 */
typedef struct {
    forward_list_node_t* head;
    size_t               element_size;
} forward_list_t;

/* 
 * This function initializes a forward list. It takes a pointer to the 
 * forward list and the size of the elements to be inserted in the 
 * list as arguments. 
 */
cstd_inline void 
cstd_forward_list_init(forward_list_t* list,
                       const size_t element_size) {
    list->head = NULL;
    list->element_size = element_size;
}

/* 
 * This function frees all the nodes in a forward_list_t list, as well 
 * as the data in each node. It does not free the list itself. 
 * 
 * For each node in the list, it will: 
 *  - Free the data in the node 
 *  - Free the node itself 
 *  - Move to the next node 
 * 
 * Once the loop is complete, it will set the list's head to NULL. 
 * 
 */ 
cstd_inline void 
cstd_forward_list_free(forward_list_t* list) {
    forward_list_node_t* current = list->head;
    forward_list_node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

/*
 * Creates a new forward_list_node_t and initializes it with the 
 * specified data.
 * 
 * Returns a pointer to the newly created node.
 */
cstd_inline forward_list_node_t* 
cstd_forward_list_create_node(
    const void* data, const size_t element_size) {
    forward_list_node_t* new_node =
        (forward_list_node_t*)malloc(sizeof(forward_list_node_t));
    new_node->data = malloc(element_size);
    memcpy(new_node->data, data, element_size);
    new_node->next = NULL;
    return new_node;
}

/*
 * Pushes an element to the front of the list.
 * The element is copied to a new node and the node is inserted at the head of
 * the list.
 */
cstd_inline void 
cstd_forward_list_push_front(forward_list_t* list,
                             void* element) {
    forward_list_node_t* new_node =
        cstd_forward_list_create_node(element, list->element_size);
    new_node->next = list->head;
    list->head = new_node;
}

/* 
 * This function removes the first element in the list. 
 */
cstd_inline void 
cstd_forward_list_pop_front(forward_list_t* list) {
    if (list->head != NULL) {
        forward_list_node_t* old_head = list->head;
        list->head = old_head->next;
        free(old_head->data);
        free(old_head);
    }
}

/*
 * Inserts a node with the given element after the given node in the list. If
 * the node is NULL, inserts the new node at the beginning of the list.
 * Returns a pointer to the newly inserted node.
 */
cstd_inline forward_list_node_t* 
cstd_forward_list_insert_after(
    forward_list_t* list, forward_list_node_t* node, void* element) {
    forward_list_node_t* new_node =
        cstd_forward_list_create_node(element, list->element_size);
    new_node->next = node->next;
    node->next = new_node;
    return new_node;
}

/* 
 * Removes the node after the given one from the list.
 * If the given node is the tail of the list, nothing happens.
 * The data stored in the node is freed.
 */
cstd_inline void 
cstd_forward_list_erase_after(forward_list_t* list,
                              forward_list_node_t* node) {
    forward_list_node_t* to_erase = node->next;
    if (to_erase != NULL) {
        node->next = to_erase->next;
        free(to_erase->data);
        free(to_erase);
    }
}

/*
 * Returns true if the list is empty, false otherwise.
 */
cstd_inline bool 
cstd_forward_list_empty(forward_list_t* list) {
    return list->head == NULL;
}

/* 
 * This function returns a pointer to the node in the list that contains the
 * given element, or NULL if it is not in the list. If the list does not
 * contain the element, the function returns NULL.
 */
cstd_inline forward_list_node_t* 
cstd_forward_list_find(
    forward_list_t* list, void* element, bool (*compare)(void*, void*)) {
    forward_list_node_t* current = list->head;
    while (current != NULL) {
        if (compare(element, current->data)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* 
 * Clears the contents of the list.
 */
cstd_inline void 
cstd_forward_list_clear(forward_list_t* list) {
    cstd_forward_list_free(list);
}

/* 
 * Returns the number of elements in the given forward_list_t. 
 */ 
cstd_inline size_t 
cstd_forward_list_size(forward_list_t* list) {
    size_t size = 0;
    forward_list_node_t* current = list->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

/* 
 * Returns a pointer to the next node in the list. 
 */
cstd_inline forward_list_node_t* 
cstd_forward_list_next(forward_list_node_t* node) {
    return node->next;
}

/* 
 * Returns the data pointer contained in the forward list node. 
 */
cstd_inline void* 
cstd_forward_list_data(forward_list_node_t* node) {
    return node->data;
}