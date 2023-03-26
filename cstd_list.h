#pragma once

#include "cstd_common.h"

typedef struct list_node {
    void* data;
    struct list_node* prev;
    struct list_node* next;
} list_node_t;

typedef struct {
    list_node_t* head;
    list_node_t* tail;
    size_t size;
    size_t element_size;
} list_t;

cstd_inline void 
cstd_list_init(list_t* lst, const size_t element_size) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
    lst->element_size = element_size;
}

cstd_inline void 
cstd_list_free(list_t* lst) {
    list_node_t* current = lst->head;
    list_node_t* next;
    while (current) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

cstd_inline list_node_t* 
cstd_list_create_node(void* data, size_t element_size) {
    list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
    node->data = malloc(element_size);
    memcpy(node->data, data, element_size);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

cstd_inline void 
cstd_list_push_back(list_t* lst, void* data) {
    list_node_t* node = cstd_list_create_node(data, lst->element_size);
    if (lst->tail) {
        lst->tail->next = node;
        node->prev = lst->tail;
    } else {
        lst->head = node;
    }
    lst->tail = node;
    lst->size++;
}

cstd_inline void 
cstd_list_push_front(list_t* lst, void* data) {
    list_node_t* node = cstd_list_create_node(data, lst->element_size);
    if (lst->head) {
        lst->head->prev = node;
        node->next = lst->head;
    } else {
        lst->tail = node;
    }
    lst->head = node;
    lst->size++;
}

cstd_inline void 
cstd_list_pop_back(list_t* lst) {
    if (lst->tail) {
        list_node_t* new_tail = lst->tail->prev;
        if (new_tail) {
            new_tail->next = NULL;
        } else {
            lst->head = NULL;
        }
        free(lst->tail->data);
        free(lst->tail);
        lst->tail = new_tail;
        lst->size--;
    }
}

cstd_inline void 
cstd_list_pop_front(list_t* lst) {
    if (lst->head) {
        list_node_t* new_head = lst->head->next;
        if (new_head) {
            new_head->prev = NULL;
        } else {
            lst->tail = NULL;
        }
        free(lst->head->data);
        free(lst->head);
        lst->head = new_head;
        lst->size--;
    }
}

cstd_inline void* 
cstd_list_at(list_t* lst, const size_t index) {
    assert(index < lst->size);
    list_node_t* current = lst->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

cstd_inline bool 
cstd_list_empty(list_t* lst) {
    return lst->size == 0;
}

cstd_inline void 
cstd_list_insert(list_t* lst, const size_t index, void* data) {
    assert(index <= lst->size);
    if (index == 0) {
        cstd_list_push_front(lst, data);
    } else if (index == lst->size) {
        cstd_list_push_back(lst, data);
    } else {
        list_node_t* current = lst->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        list_node_t* new_node = cstd_list_create_node(data, lst->element_size);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        lst->size++;
    }
}

cstd_inline void 
cstd_list_erase(list_t* lst, const size_t index) {
    assert(index < lst->size);
    if (index == 0) {
        cstd_list_pop_front(lst);
    } else if (index == lst->size - 1) {
        cstd_list_pop_back(lst);
    } else {
        list_node_t* current = lst->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current->data);
        free(current);
        lst->size--;
    }
}

cstd_inline void 
cstd_list_clear(list_t* lst) {
    while (!cstd_list_empty(lst)) {
        cstd_list_pop_front(lst);
    }
}

cstd_inline size_t 
cstd_list_size(list_t* lst) {
    return lst->size;
}
