#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef enum {
    RED = 0,
    BLACK = 1
} Color;

typedef struct node {
    data_t data;
    Color color;
    struct node *left;
    struct node *right;
    struct node *parent;
} tree_t;

/* Core operations required by design specification */
int insert(tree_t **root, data_t item);
int delete(tree_t **root, data_t item);
int find_minimum(tree_t **root, data_t *min);
int find_maximum(tree_t **root, data_t *max);
int delete_minimum(tree_t **root);
int delete_maximum(tree_t **root);

/* Helper operations */
tree_t *search(tree_t *root, data_t item);
void print_tree(tree_t *root);
void left_rotate(tree_t **root, tree_t *x);
void right_rotate(tree_t **root, tree_t *y);
void free_tree(tree_t *root);

#endif