#include "rbt.h"

static tree_t *tree_minimum_node(tree_t *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

static void delete_fixup(tree_t **root, tree_t *x, tree_t *x_parent) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x_parent->left) {
            tree_t *w = x_parent->right; /* Sibling */

            /* Case 1: Sibling w is RED */
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x_parent->color = RED;
                left_rotate(root, x_parent);
                w = x_parent->right;
            }

            if (w == NULL) {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            /* Case 2: Both of w's children are BLACK */
            if ((w->left == NULL || w->left->color == BLACK) &&
                (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x_parent;
                x_parent = x->parent;
            } else {
                /* Case 3: w's right child is BLACK, left child is RED */
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) {
                        w->left->color = BLACK;
                    }
                    w->color = RED;
                    right_rotate(root, w);
                    w = x_parent->right;
                }

                /* Case 4: w's right child is RED */
                w->color = x_parent->color;
                x_parent->color = BLACK;
                if (w->right != NULL) {
                    w->right->color = BLACK;
                }
                left_rotate(root, x_parent);
                x = *root;
            }
        } else {
            tree_t *w = x_parent->left; /* Sibling */

            /* Case 1: Sibling w is RED */
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x_parent->color = RED;
                right_rotate(root, x_parent);
                w = x_parent->left;
            }

            if (w == NULL) {
                x = x_parent;
                x_parent = x->parent;
                continue;
            }

            /* Case 2: Both of w's children are BLACK */
            if ((w->right == NULL || w->right->color == BLACK) &&
                (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x_parent;
                x_parent = x->parent;
            } else {
                /* Case 3: w's left child is BLACK, right child is RED */
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL) {
                        w->right->color = BLACK;
                    }
                    w->color = RED;
                    left_rotate(root, w);
                    w = x_parent->left;
                }

                /* Case 4: w's left child is RED */
                w->color = x_parent->color;
                x_parent->color = BLACK;
                if (w->left != NULL) {
                    w->left->color = BLACK;
                }
                right_rotate(root, x_parent);
                x = *root;
            }
        }
    }

    if (x != NULL) {
        x->color = BLACK;
    }
}

int delete(tree_t **root, data_t item) {
    if (root == NULL || *root == NULL) {
        return FAILURE;
    }

    tree_t *z = search(*root, item);
    if (z == NULL) {
        return FAILURE;
    }

    tree_t *y = z; /* Node to be physically unlinked */
    if (z->left != NULL && z->right != NULL) {
        y = tree_minimum_node(z->right);
        printf("successor data: %d\n", y->data);
        z->data = y->data;
    }

    tree_t *x = (y->left != NULL) ? y->left : y->right;
    tree_t *x_parent = y->parent;
    Color y_original_color = y->color;

    if (x != NULL) {
        x->parent = x_parent;
    }

    if (x_parent == NULL) {
        *root = x;
    } else if (y == x_parent->left) {
        x_parent->left = x;
    } else {
        x_parent->right = x;
    }

    free(y);

    if (y_original_color == BLACK && *root != NULL) {
        delete_fixup(root, x, x_parent);
    }

    return SUCCESS;
}