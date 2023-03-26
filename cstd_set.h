#pragma once

#include "cstd_common.h"

typedef struct avl_node {
    void* key;
    int height;
    struct avl_node* left;
    struct avl_node* right;
} avl_node_t;

typedef int (*compare_func_t)(const void* a, const void* b);

typedef struct {
    avl_node_t* root;
    size_t size;
    size_t key_size;
    compare_func_t compare;
} cstd_set_t;

cstd_inline int 
max(int a, int b) {
    return (a > b) ? a : b;
}

cstd_inline int 
height(avl_node_t* node) {
    return node ? node->height : 0;
}

cstd_inline int 
balance_factor(avl_node_t* node) {
    return height(node->left) - height(node->right);
}

cstd_inline void 
update_height(avl_node_t* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

cstd_inline avl_node_t* 
rotate_right(avl_node_t* node) {
    avl_node_t* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;

    update_height(node);
    update_height(left_child);

    return left_child;
}

cstd_inline avl_node_t* 
rotate_left(avl_node_t* node) {
    avl_node_t* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;

    update_height(node);
    update_height(right_child);

    return right_child;
}

cstd_inline avl_node_t* 
balance(avl_node_t* node) {
    update_height(node);

    if (balance_factor(node) == 2) {
        if (balance_factor(node->left) < 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    } else if (balance_factor(node) == -2) {
        if (balance_factor(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }

    return node;
}

cstd_inline avl_node_t* 
new_node(const void* key, size_t key_size) {
    avl_node_t* node = (avl_node_t*) malloc(sizeof(avl_node_t));
    node->key = malloc(key_size);
    memcpy(node->key, key, key_size);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

cstd_inline void 
free_node(avl_node_t* node) {
    free(node->key);
    free(node);
}

cstd_inline avl_node_t* 
insert(avl_node_t* node, const void* key, size_t key_size, compare_func_t compare, bool* inserted) {
    if (!node) {
        *inserted = true;
        return new_node(key, key_size);
    }

    int cmp = compare(key, node->key);
    if (cmp < 0) {
        node->left = insert(node->left, key, key_size, compare, inserted);
    } else if (cmp > 0) {
        node->right = insert(node->right, key, key_size, compare, inserted);
    } else {
        *inserted = false;
        return node;
    }

    return balance(node);
}

cstd_inline void 
cstd_set_init(cstd_set_t* set, size_t key_size, compare_func_t compare) {
    set->root = NULL;
    set->size = 0;
    set->key_size = key_size;
    set->compare = compare;
}

cstd_inline void 
cstd_set_clear_recursive(avl_node_t* node) {
    if (!node) {
        return;
    }

    cstd_set_clear_recursive(node->left);
    cstd_set_clear_recursive(node->right);
    free_node(node);
}

cstd_inline void 
cstd_set_clear(cstd_set_t* set) {
    cstd_set_clear_recursive(set->root);
    set->root = NULL;
    set->size = 0;
}

cstd_inline bool 
cstd_set_insert(cstd_set_t* set, const void* key) {
    bool inserted;
    set->root = insert(set->root, key, set->key_size, set->compare, &inserted);
    if (inserted) {
        set->size++;
    }
    return inserted;
}

cstd_inline avl_node_t* 
find_min(avl_node_t* node) {
    return node->left ? find_min(node->left) : node;
}

cstd_inline avl_node_t* 
remove_min(avl_node_t* node) {
    if (!node->left) {
        return node->right;
    }
    node->left = remove_min(node->left);
    return balance(node);
}

cstd_inline avl_node_t* 
remove_node(avl_node_t* node, const void* key, size_t key_size, compare_func_t compare, bool* removed) {
    if (!node) {
        *removed = false;
        return NULL;
    }

    int cmp = compare(key, node->key);
    if (cmp < 0) {
        node->left = remove_node(node->left, key, key_size, compare, removed);
    } else if (cmp > 0) {
        node->right = remove_node(node->right, key, key_size, compare, removed);
    } else {
        avl_node_t* left = node->left;
        avl_node_t* right = node->right;
        free_node(node);

        if (!right) {
            *removed = true;
            return left;
        }

        avl_node_t* min = find_min(right);
        min->right = remove_min(right);
        min->left = left;

        *removed = true;
        return balance(min);
    }

    return balance(node);
}

cstd_inline bool 
cstd_set_erase(cstd_set_t* set, const void* key) {
    bool removed;
    set->root = remove_node(set->root, key, set->key_size, set->compare, &removed);
    if (removed) {
        set->size--;
    }
    return removed;
}

cstd_inline bool 
cstd_set_contains_recursive(avl_node_t* node, const void* key, compare_func_t compare) {
    if (!node) {
        return false;
    }

    int cmp = compare(key, node->key);
    if (cmp == 0) {
        return true;
    }
    return cmp < 0 ? cstd_set_contains_recursive(node->left, key, compare) :
                     cstd_set_contains_recursive(node->right, key, compare);
}

cstd_inline bool 
cstd_set_contains(cstd_set_t* set, const void* key) {
    return cstd_set_contains_recursive(set->root, key, set->compare);
}

cstd_inline size_t 
cstd_set_size(cstd_set_t* set) {
    return set->size;
}

cstd_inline bool 
cstd_set_empty(cstd_set_t* set) {
    return set->size == 0;
}

cstd_inline void 
cstd_set_free(cstd_set_t* set) {
    cstd_set_clear(set);
}
