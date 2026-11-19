#include "rbt.h"

tree_t *search(tree_t *root, data_t item) {
    tree_t *curr = root;
    while (curr != NULL) {
        if (item == curr->data) {
            return curr;
        } else if (item < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

int find_minimum(tree_t **root, data_t *min) {
    if (root == NULL || *root == NULL || min == NULL) {
        return FAILURE;
    }

    tree_t *curr = *root;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    *min = curr->data;
    return SUCCESS;
}

int find_maximum(tree_t **root, data_t *max) {
    if (root == NULL || *root == NULL || max == NULL) {
        return FAILURE;
    }

    tree_t *curr = *root;
    while (curr->right != NULL) {
        curr = curr->right;
    }
    *max = curr->data;
    return SUCCESS;
}

int delete_minimum(tree_t **root) {
    data_t min;
    if (find_minimum(root, &min) == FAILURE) {
        return FAILURE;
    }
    return delete(root, min);
}

int delete_maximum(tree_t **root) {
    data_t max;
    if (find_maximum(root, &max) == FAILURE) {
        return FAILURE;
    }
    return delete(root, max);
}