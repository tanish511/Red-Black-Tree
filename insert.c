#include "rbt.h"

void left_rotate(tree_t **root, tree_t *x) {
    if (x == NULL || x->right == NULL) return;

    tree_t *y = x->right;
    x->right = y->left;

    if (y->left != NULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void right_rotate(tree_t **root, tree_t *y) {
    if (y == NULL || y->left == NULL) return;

    tree_t *x = y->left;
    y->left = x->right;

    if (x->right != NULL) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

static void insert_fixup(tree_t **root, tree_t *z) {
    while (z != *root && z->parent->color == RED) {
        tree_t *parent = z->parent;
        tree_t *grandparent = parent->parent;

        if (parent == grandparent->left) {
            tree_t *uncle = grandparent->right;

            /* Case 1: Uncle is RED -> Recolor */
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                /* Case 2: Uncle is BLACK and z is right child (LR) */
                if (z == parent->right) {
                    z = parent;
                    left_rotate(root, z);
                    parent = z->parent;
                    grandparent = parent->parent;
                }
                /* Case 3: Uncle is BLACK and z is left child (LL) */
                parent->color = BLACK;
                grandparent->color = RED;
                right_rotate(root, grandparent);
            }
        } else {
            tree_t *uncle = grandparent->left;

            /* Case 1: Uncle is RED -> Recolor */
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                /* Case 2: Uncle is BLACK and z is left child (RL) */
                if (z == parent->left) {
                    z = parent;
                    right_rotate(root, z);
                    parent = z->parent;
                    grandparent = parent->parent;
                }
                /* Case 3: Uncle is BLACK and z is right child (RR) */
                parent->color = BLACK;
                grandparent->color = RED;
                left_rotate(root, grandparent);
            }
        }
    }
    (*root)->color = BLACK;
}

int insert(tree_t **root, data_t item) {
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
    if (new_node == NULL) {
        return FAILURE;
    }

    new_node->data = item;
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    /* If tree is empty, new node becomes BLACK root */
    if (*root == NULL) {
        new_node->color = BLACK;
        *root = new_node;
        return SUCCESS;
    }

    /* Standard BST insertion */
    tree_t *curr = *root;
    tree_t *parent = NULL;

    while (curr != NULL) {
        parent = curr;
        if (item < curr->data) {
            curr = curr->left;
        } else if (item > curr->data) {
            curr = curr->right;
        } else {
            free(new_node); /* Duplicate key */
            return FAILURE;
        }
    }

    new_node->parent = parent;
    if (item < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    printf("Before Balancing Red Black Tree is:\n");
    print_tree(*root);
    printf("\n");

    insert_fixup(root, new_node);

    printf("Now Tree is balance:\n");
    print_tree(*root);
    printf("\n");

    return SUCCESS;
}