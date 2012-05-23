/*
 * This  file defines the AVL-tree data structure. It contains functions for 
 * adding a word to the tree, rotate-operations for balancing the tree in order
 * it to fullfill the AVL-tree -requirements, function for printing out 
 * the contents of the tree, function for destroying the tree and several 
 * functions to assist the implementation.
 * File has functions node* add_word(node* n), node* single_rotate_left(node* n),
 * node* single_rotate_right(node* n), node* double_rotate_left(node* n), 
 * node* double_rotate_right(node* n), void print_words(node *n, FILE* out), 
 * int get_height(node* n), int get_max(int a, int b), node* destroy(node *n)
 * Author: MK
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sentenced.h"

/*
 *This method adds word to the tree and calls for rotate-functions if needed.
 * If word already exists, it updates the count.
 * Parameters: node* p (root of the tree), char* w (word to be added)
 * Returns node* (new root of the tree) 
 */
node *add_word(node *p, char *w) {

    int new_word_value;

    if (p == NULL) { /* new word */
        p = malloc(sizeof (node));
        p->word = strdup(w);
        p->count = 1;
        p->height = 0;
        p->left = NULL;
        p->right = NULL;

    } else
        if ((new_word_value = strcmp(w, p->word)) == 0){ /* word already exists*/
        p->count++;
        }
    else
        if (new_word_value < 0) { /* word has lower presedence -> left child*/
            p->left = add_word(p->left, w);
            if (get_height(p->left) - get_height(p->right) == 2) {
                if (strcmp(w, p->left->word) < 0) {
                    p = single_rotate_left(p);
            } else {
                p = double_rotate_left(p);
            }
        }
    }
        else { /* word has higher presedence -> right child*/
        p->right = add_word(p->right, w);
        if (get_height(p->right) - get_height(p->left) == 2) {
            if (strcmp(w, p->right->word) > 0) {
                p = single_rotate_right(p);
            } else {
                p = double_rotate_right(p);
            }
        }
    }
    p->height = get_max(get_height(p->left), get_height(p->right)) + 1;
    return p;
}

/*
 * This method does the single rotate left -procedure to balance the tree
 * Parameter: node* node2 (position of tree where rotation should take place)
 * Returns: node*  (the new root of subtree)
 */
node *single_rotate_left(node* node2) {
    node* node1;
    node1 = node2->left;
    node2->left = node1->right;
    node1->right = node2;
    node2->height = get_max(get_height(node2->left), get_height(node2->right)) + 1;
    node1->height = get_max(get_height(node1->left), node2->height) + 1;
    return node1;
}

/*
 * This method does the single rotate right -procedure to balance the tree
 * Parameter: node* node1 (position of tree where rotation should take place)
 * Returns: node*  (the new root of subtree)
 */
node *single_rotate_right(node* node1) {
    node* node2;
    node2 = node1->right;
    node1->right = node2->left;
    node2->left = node1;
    node1->height = get_max(get_height(node1->left), get_height(node1->right)) + 1;
    node2->height = get_max(get_height(node2->left), node1->height) + 1;
    return node2;
}

/*
 * This method does the double rotate left -procedure to balance the tree
 * Parameter: node* node3 (position of tree where rotation should take place)
 * Returns: node* (the new root of subtree)
 */
node *double_rotate_left(node* node3) {
    node3->left = single_rotate_right(node3->left);
    return single_rotate_left(node3);
}

/*
 * This method does the single rotate right -procedure to balance the tree
 * Parameter: node* node1 (position of tree where rotation should take place)
 * Returns: node* (the new root of subtree)
 */
node *double_rotate_right(node* node1) {
    node1->right = single_rotate_left(node1->right);
    return single_rotate_right(node1);
}

/*
 * This function prints the contents of the tree recursively.
 * Parameters: node* p (root of the tree), FILE* out (output stream)
 */

void print_words(node *p, FILE* out) {
    if (p != NULL) {

        print_words(p->left,out);
        printf("%s %d\n", p->word, p->count);
        fprintf(out,"%s %d\n", p->word, p->count);
        print_words(p->right, out);
    }
}

/*
 * This function returns height of the node
 * Parameter: node* n (position of the tree of which the height is returned)
 * Returns: int (the height value of the node)
 */
int get_height(node* n) {
    if (n == NULL)
        return -1;
    else
        return n->height;
}

/*
 * This function returns the higher value of two integers
 * Parameters: int a, int b (the values to be compared)
 * Returns: int (higher value of the two integers given as parameters)
 */
int get_max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

/*
 * This function destroys the tree and frees the memory allocated to the nodes.
 * Parameter: node* n (root of the trees)
 * Returns node* (NULL-pointer)
 */
node* destroy(node *n) {
    if(n != NULL) {
        destroy(n->left);
        destroy(n->right);
        free(n);
    }
    return NULL;
}

