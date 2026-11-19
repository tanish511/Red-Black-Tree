#include "rbt.h"

void print_tree(tree_t *root) {
    if (root == NULL) {
        return;
    }
    print_tree(root->left);
    printf("(%d)--(%s->%d) ",
           root->data,
           (root->color == RED) ? "RED" : "BLACK",
           root->color);
    print_tree(root->right);
}

void free_tree(tree_t *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}