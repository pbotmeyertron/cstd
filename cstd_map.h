#pragma once

#include "cstd_common.h"

typedef struct node_t {
    void*          key;
    void*          value;
    int32_t        height;
    struct node_t* left;
    struct node_t* right;
} node_t;

typedef struct map_t {
    node_t* root;
    size_t  size;
    size_t  key_size;
    size_t  value_size;
    int32_t (*key_compare)(const void *, const void *);
} map_t;

cstd_inline int32_t 
max(const int32_t a, const int32_t b) {
    return (a > b) ? a : b;
}

cstd_inline int32_t 
height(node_t* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

cstd_inline int32_t 
balance_factor(node_t* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

cstd_inline node_t* 
new_node(const void* key, 
         const void* value, 
         const size_t key_size, 
         const size_t value_size) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }

    node->key = malloc(key_size);
    if (!node->key) {
        free(node);
        return NULL;
    }

    node->value = malloc(value_size);
    if (!node->value) {
        free(node->key);
        free(node);
        return NULL;
    }

    memcpy(node->key, key, key_size);
    memcpy(node->value, value, value_size);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

cstd_inline node_t* 
right_rotate(node_t *y) {
    node_t* x  = y->left;
    node_t* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

cstd_inline node_t* 
left_rotate(node_t *x) {
    node_t* y  = x->right;
    node_t* T2 = y->left;
    y->left   = x;
    x->right  = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

cstd_inline node_t* 
insert_recursive(map_t* map, node_t* node, 
                 const void* key, const void* value) {
    if (node == NULL) {
        return new_node(key, value, map->key_size, map->value_size);
    }
    int32_t cmp = map->key_compare(key, node->key);
    if (cmp < 0) {
        node->left = insert_recursive(map, node->left, key, value);
    } else if (cmp > 0) {
        node->right = insert_recursive(map, node->right, key, value);
    } else {
        memcpy(node->value, value, map->value_size);
        return node;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    int32_t balance = balance_factor(node);
    // Left Left case
    if (balance > 1 && map->key_compare(key, node->left->key) < 0) {
        return right_rotate(node);
    }
    // Right Right case
    if (balance < -1 && map->key_compare(key, node->right->key) > 0) {
        return left_rotate(node);
    }
    // Left Right case
    if (balance > 1 && map->key_compare(key, node->left->key) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    // Right Left case
    if (balance < -1 && map->key_compare(key, node->right->key) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

cstd_inline node_t* 
find_minimum(node_t* node) {
    if (node->left == NULL) {
        return node;
    }
    return find_minimum(node->left);
}

cstd_inline node_t* 
delete_recursive(map_t*  map, 
                 node_t* root, 
                 const void* key) {
    if (root == NULL) {
        return root;
    }

    int32_t cmp = map->key_compare(key, root->key);
    if (cmp < 0) {
        root->left = delete_recursive(map, root->left, key);
    } else if (cmp > 0) {
        root->right = delete_recursive(map, root->right, key);
    } else {
        if (root->left == NULL || root->right == NULL) {
            node_t *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp->key);
            free(temp->value);
            free(temp);
        } else {
            node_t* temp = find_minimum(root->right);
            memcpy(root->key, temp->key, map->key_size);
            memcpy(root->value, temp->value, map->value_size);
            root->right = delete_recursive(map, root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int32_t balance = balance_factor(root);

    // Left Left case
    if (balance > 1 && balance_factor(root->left) >= 0) {
        return right_rotate(root);
    }

    // Left Right case
    if (balance > 1 && balance_factor(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Right case
    if (balance < -1 && balance_factor(root->right) <= 0) {
        return left_rotate(root);
    }

    // Right Left case
    if (balance < -1 && balance_factor(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

cstd_inline void 
free_tree(node_t* node) {
    if (node == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node->key);
    free(node->value);
    free(node);
}

cstd_inline void 
cstd_map_init(map_t *map, 
              const size_t key_size, 
              const size_t value_size, 
              int32_t (*key_compare)(const void *, const void *)) {
    map->root = NULL;
    map->size = 0;
    map->key_size = key_size;
    map->value_size = value_size;
    map->key_compare = key_compare;
}

cstd_inline bool
inserted_new_key(map_t* map, node_t* node, const void* key, const void* value) {
    if (node == NULL) {
        node = new_node(key, value, map->key_size, map->value_size);
        if (!node) {
            return false;
        }
        return true;
    }
    int32_t cmp = map->key_compare(key, node->key);
    if (cmp < 0) {
        return inserted_new_key(map, node->left, key, value);
    } else if (cmp > 0) {
        return inserted_new_key(map, node->right, key, value);
    } else {
        memcpy(node->value, value, map->value_size);
        return false;
    }
}

cstd_inline void 
cstd_map_insert(map_t* map, const void* key, const void *value) {
    if (inserted_new_key(map, map->root, key, value)) {
        map->root = insert_recursive(map, map->root, key, value);
        map->size++;
    }
}

cstd_inline void* 
cstd_map_find(map_t *map, const void *key) {
    node_t *current = map->root;
    while (current) {
        int cmp = map->key_compare(key, current->key);
        if (cmp == 0) {
            return current->value;
        }
        current = (cmp < 0) ? current->left : current->right;
    }
    return NULL;
}

cstd_inline void 
cstd_map_delete(map_t* map, const void* key) {
    if (cstd_map_find(map, key)) {
        map->root = delete_recursive(map, map->root, key);
        map->size--;
    }
}

cstd_inline size_t 
cstd_map_size(map_t* map) {
    return map->size;
}

cstd_inline bool 
cstd_map_empty(map_t* map) {
    return map->size == 0;
}

cstd_inline void 
cstd_map_clear(map_t* map) {
    free_tree(map->root);
    map->root = NULL;
    map->size = 0;
}

cstd_inline void 
cstd_map_free(map_t* map) {
    free_tree(map->root);
    map->root = NULL;
    map->size = 0;
}