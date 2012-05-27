/*
 * This file contains list of function defined in program files so they 
 * can be called anywhere where this header file is included. Also struct node
 * is definend here.
 * Author: MK
 */

#ifndef SENTENCED_H
#define﻿  SENTENCED_H

#ifdef﻿  __cplusplus
extern "C" {
#endif




#ifdef﻿  __cplusplus
}
#endif

#endif﻿  /* SENTENCED_H */

void readfile(FILE*);
typedef struct node {
    char *word;
    int count;
    int height;
    struct node *left;
    struct node *right;
} node;

void read_words(FILE*, FILE*);
node *add_word(node*, char*);
node *single_rotate_left(node*);
node *single_rotate_right(node*);
node *double_rotate_left(node*);
node *double_rotate_right(node*);
void print_words(node*, FILE*);
int get_height(node*);
int get_max(int a, int b);
node* destroy(node *n);
void help(void);
void info(void);
void error(int err_code);
void validate_tree(node*);
void run_test();
