/*
 *This file contains functions for testing the AVL-tree data structure implemented 
 *in avltree.c. 
 *File has functions void run_tests(), void validate_tree(node* n*) 
 *File uses function node* n add_word(node* n, char* word), void print_words(node* n, FILE* pt)
 *and node* destroy_tree(node* n) from avltree.c.
 * Author: HK
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sentenced.h"
#include <math.h>

/*
 * This function validates the AVL-tree by checking if the height difference between 
 * child-nodes is adequate and the word-order in the tree is correct.
 * Parameter: node* n
 */
void validate_tree(node *n) {

    if (n != NULL) {
         
        if (n->right != NULL && n->left != NULL) {
            if (abs(get_height(n->right) - get_height(n->left)) >= 2) {
                printf("Height difference too big");
                exit(EXIT_FAILURE);
            }
            if (strcmp(n->word, n->left->word) < 0) {
                printf("inappropriate word-order, left child");
                exit(EXIT_FAILURE);
            }

            if (strcmp(n->word, n->right->word) > 0) {
                printf("inappropriate word-order, right child");
                exit(EXIT_FAILURE);
            }
            validate_tree(n->left);
            validate_tree(n->right);
        } else if (n->right == NULL && n->left != NULL) {
            if (abs(get_height(n->right) - get_height(n->left)) >= 2) {
                printf("Height difference too big");
                exit(EXIT_FAILURE);
            }
            if (strcmp(n->word, n->left->word) < 0) {
                printf("inappropriate word-order, left child");
                exit(EXIT_FAILURE);
            }
            validate_tree(n->left);


        } else if (n->right != NULL && n->left == NULL) {
            if (abs(get_height(n->right) - get_height(n->left)) >= 2) {
                printf("Height difference too big");
                exit(EXIT_FAILURE);
            }
            if (strcmp(n->word, n->right->word) > 0) {
                printf("inappropriate word-order, right child");
                exit(EXIT_FAILURE);
            }
            validate_tree(n->right);
        }
    }
}

/*
 * This function adds words in different orders and amounts to the AVL-tree. 
 * After adding, it validates the AVL-tree. Function prints the results to stdout. 
 */
void run_test() {

    node* root;
    FILE* out;
    root = NULL;
    int i;
    char* test_strings[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};

    if ((out = fopen("tree_test_result.txt", "w")) == NULL) {
        fprintf(stderr, "Cannot write to output file tree_test_result\n");
        exit(1);
    }
  
    /*Add words in increasing order*/
    printf("\nAdd words in increasing order:\n");
    for (i = 0; i < 11; i++) {
        root = add_word(root, test_strings[i]);
    }
    printf("Run validation\n");
    validate_tree(root);
    printf("Test passed\n");
    print_words(root, out);
    destroy(root);

    /*Add words in decreasing order*/
    root = NULL;
    printf("\nAdd words in decreasing order:\n");
    for (i = 10; i >= 0; i--) {
        root = add_word(root, test_strings[i]);
    }
    printf("Run validation\n");
    validate_tree(root);
    printf("Test passed\n");
    print_words(root, out);
    destroy(root);

    /*Add only one word*/
    root = NULL;
    printf("\nAdd single word:\n");
    root = add_word(root, test_strings[0]);
    printf("Run validation\n");
    validate_tree(root);
    printf("Test passed\n");
    print_words(root, out);
    destroy(root);
    fclose(out);
    
    exit(0);


}


