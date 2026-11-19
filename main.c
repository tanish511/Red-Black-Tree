#include "rbt.h"

int main(void) {
    tree_t *root = NULL;
    int choice;
    data_t item, min, max;
    char cont;

    while (1) {
        printf("\n1. Create a tree\n");
        printf("2. Display\n");
        printf("3. Search a node\n");
        printf("4. Find Maximum node in Tree\n");
        printf("5. Find Minimum node in Tree\n");
        printf("6. Deletion\n");
        printf("7. Delete Minimum node\n");
        printf("8. Delete Maximum Node\n");
        printf("9. Exit\n");
        printf("Enter the choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                do {
                    printf("Enter the element: ");
                    scanf("%d", &item);
                    if (insert(&root, item) == FAILURE) {
                        printf("INFO: Insertion failed (duplicate or memory error)\n");
                    }
                    printf("Do u want to continue (y/n): ");
                    scanf(" %c", &cont);
                } while (cont == 'y' || cont == 'Y');
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else {
                    printf("Display ");
                    print_tree(root);
                    printf("\n");
                }
                break;

            case 3: {
                printf("Enter the element which u want to search from the red black tree: ");
                scanf("%d", &item);
                tree_t *found = search(root, item);
                if (found != NULL) {
                    printf("Node is found (%d)--(%s->%d)\n",
                           found->data,
                           (found->color == RED) ? "RED" : "BLACK",
                           found->color);
                } else {
                    printf("Node (%d) not found in the tree\n", item);
                }
                break;
            }

            case 4:
                if (find_maximum(&root, &max) == SUCCESS) {
                    tree_t *max_node = search(root, max);
                    printf("Maximum node in the given Red Black Tree is (%d)--(%s->%d)\n",
                           max_node->data,
                           (max_node->color == RED) ? "RED" : "BLACK",
                           max_node->color);
                } else {
                    printf("Tree is empty\n");
                }
                break;

            case 5:
                if (find_minimum(&root, &min) == SUCCESS) {
                    tree_t *min_node = search(root, min);
                    printf("Minimum node in the given Red Black Tree is (%d)--(%s->%d)\n",
                           min_node->data,
                           (min_node->color == RED) ? "RED" : "BLACK",
                           min_node->color);
                } else {
                    printf("Tree is empty\n");
                }
                break;

            case 6:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else {
                    printf("Enter the node which u want to delete: ");
                    scanf("%d", &item);
                    if (delete(&root, item) == FAILURE) {
                        printf("Node (%d) not found in the tree\n", item);
                    }
                }
                break;

            case 7:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else {
                    printf("Tree Before deleting the minimum node:\n");
                    print_tree(root);
                    printf("\n");
                    delete_minimum(&root);
                    printf("Tree After deleting the minimum node:\n");
                    if (root != NULL) {
                        print_tree(root);
                    } else {
                        printf("Tree is now empty");
                    }
                    printf("\n");
                }
                break;

            case 8:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else {
                    printf("Tree Before deleting the maximum node:\n");
                    print_tree(root);
                    printf("\n");
                    delete_maximum(&root);
                    printf("Tree After deleting the maximum node:\n");
                    if (root != NULL) {
                        print_tree(root);
                    } else {
                        printf("Tree is now empty");
                    }
                    printf("\n");
                }
                break;

            case 9:
                free_tree(root);
                return 0;

            default:
                printf("Invalid choice! Please select between 1 and 9.\n");
        }
    }
}