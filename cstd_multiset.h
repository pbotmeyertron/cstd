#pragma once

#include "cstd_common.h"

typedef struct bst_node {
    void* data;
    struct bst_node* left;
    struct bst_node* right;
    unsigned int count;
} bst_node_t;

typedef struct {
    bst_node_t* root;
    size_t element_size;
    int (*compare)(const void*, const void*);
} multiset_t;

cstd_inline void cstd_multiset_init(multiset_t* set, const size_t element_size,
                                    int (*compare)(const void*, const void*)) {
    set->root = NULL;
    set->element_size = element_size;
    set->compare = compare;
}

cstd_inline void cstd_multiset_free_nodes(bst_node_t* node) {
    if (node != NULL) {
        cstd_multiset_free_nodes(node->left);
        cstd_multiset_free_nodes(node->right);
        free(node->data);
        free(node);
    }
}

cstd_inline void cstd_multiset_free(multiset_t* set) {
    cstd_multiset_free_nodes(set->root);
    set->root = NULL;
}

cstd_inline bst_node_t* cstd_multiset_create_node(const void* data,
                                                  const size_t element_size) {
    bst_node_t* new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    new_node->data = malloc(element_size);
    memcpy(new_node->data, data, element_size);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->count = 1;
    return new_node;
}

cstd_inline void cstd_multiset_insert_node(multiset_t* set, bst_node_t** node,
                                           const void* data) {
    if (*node == NULL) {
        *node = cstd_multiset_create_node(data, set->element_size);
    } else {
        int comparison = set->compare(data, (*node)->data);
        if (comparison < 0) {
            cstd_multiset_insert_node(set, &((*node)->left), data);
        } else if (comparison > 0) {
            cstd_multiset_insert_node(set, &((*node)->right), data);
        } else {
            (*node)->count++;
        }
    }
}

cstd_inline void cstd_multiset_insert(multiset_t* set, void* data) {
    cstd_multiset_insert_node(set, &(set->root), data);
}

cstd_inline bst_node_t* cstd_multiset_find_node(const multiset_t* set,
                                                bst_node_t* node,
                                                const void* data) {
    if (node == NULL) {
        return NULL;
    }

    int comparison = set->compare(data, node->data);
    if (comparison < 0) {
        return cstd_multiset_find_node(set, node->left, data);
    } else if (comparison > 0) {
        return cstd_multiset_find_node(set, node->right, data);
    } else {
        return node;
    }
}

cstd_inline bst_node_t* cstd_multiset_find(const multiset_t* set, void* data) {
    return cstd_multiset_find_node(set, set->root, data);
}

cstd_inline bool cstd_multiset_empty(const multiset_t* set) {
    return set->root == NULL;
}

cstd_inline size_t cstd_multiset_size_node(const bst_node_t* node) {
    if (node == NULL) {
        return 0;
    }
    return node->count + cstd_multiset_size_node(node->left) +
           cstd_multiset_size_node(node->right);
}

cstd_inline size_t cstd_multiset_size(const multiset_t* set) {
    return cstd_multiset_size_node(set->root);
}

cstd_inline bst_node_t* cstd_multiset_min_node(bst_node_t* node) {
    if (node->left == NULL) {
        return node;
    }
    return cstd_multiset_min_node(node->left);
}

cstd_inline bst_node_t* cstd_multiset_remove_min_node(multiset_t* set,
                                                      bst_node_t* node) {
    if (node->left == NULL) {
        bst_node_t* right = node->right;
        free(node->data);
        free(node);
        return right;
    }
    node->left = cstd_multiset_remove_min_node(set, node->left);
    return node;
}

cstd_inline bst_node_t* cstd_multiset_remove_node(multiset_t* set,
                                                  bst_node_t* node,
                                                  const void* data) {
    if (node == NULL) {
        return NULL;
    }

    int comparison = set->compare(data, node->data);
    if (comparison < 0) {
        node->left = cstd_multiset_remove_node(set, node->left, data);
    } else if (comparison > 0) {
        node->right = cstd_multiset_remove_node(set, node->right, data);
    } else {
        if (node->count > 1) {
            node->count--;
        } else {
            if (node->left == NULL) {
                bst_node_t* right = node->right;
                free(node->data);
                free(node);
                return right;
            }
            if (node->right == NULL) {
                bst_node_t* left = node->left;
                free(node->data);
                free(node);
                return left;
            }
            bst_node_t* min_right = cstd_multiset_min_node(node->right);
            memcpy(node->data, min_right->data, set->element_size);
            node->count = min_right->count;
            node->right = cstd_multiset_remove_min_node(set, node->right);
        }
    }
    return node;
}

cstd_inline void cstd_multiset_remove(multiset_t* set, void* data) {
    set->root = cstd_multiset_remove_node(set, set->root, data);
}

cstd_inline void* cstd_multiset_data(const bst_node_t* node) {
    return node->data;
}

cstd_inline unsigned int cstd_multiset_count(const bst_node_t* node) {
    return node->count;
}
