/*
 * This file contains functions to read strings from input stream and to 
 * trim them before adding to the data structure and to print results to file 
 * and stdout. 
 * File has functions char* trim(char* word), read_words(FILE* in, FILE* out)
 * File calls functions void print_words(node*, FILE*) 
 * and node *add_word(node*, char*) from avltree.c.
 * Author: HK
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sentenced.h"
#include <stdbool.h>
#define BUFSIZE 100

/*
 * This function removes extra-characters from the beginning and from the end of
 * the string given as parameter.
 * Parameter: char* word (string to be trimmed)
 * Returns: char* (trimmed string) 
 */
char* trim(char* word) {

    /*trim end of string*/
    int i = strlen(word);
    while (1) {

        if (!isalnum(word[i])) {
            word[i] = '\0';
            i--;
        } else
            break;
    }

    /*trim beginning of string*/
    while (1) {
        if (!isalnum(word[0])) {
            word++;
        } else
            break;
    }

    return word;

}

/*
 * This function reads strings from input stream, either a file stream or stdin.
 * Function also prints the results to file and stdout.
 * Parameters: FILE* in (input filestream), FILE* out (output stream)
 */
void read_words(FILE* in, FILE* out) {

    bool alpha_numeric_word = false; 
    char* temp;
    char* buf = malloc(sizeof (char) * BUFSIZE);
    int* words_in_sentences = malloc(sizeof (int) * 100);
    node *root;
    unsigned int i, sentences, words, temp_word;
    root = NULL;
    i = sentences = words = temp_word = 0;

    for (i = 0; i < 100; i++) {
        words_in_sentences[i] = 0;
    }
    while (true) {
        fscanf(in, "%99s", buf);
        if (feof(in))
            break;
        words++;
        temp_word++;
        temp = buf;

        /*remove full comma from the end and  update sentences*/
        if (temp[strlen(temp) - 1] == '.' && (!isdigit(temp[strlen(temp) - 2]))) {
            temp[strlen(temp) - 1] = '\0'; 
            sentences++;
            if (temp_word < 100)
                ++words_in_sentences[temp_word];
            temp_word = 0;
        }
    /*check if the string doesn't contain alphanumerics at all*/
        for(i = 0; i < strlen(buf); i++){
       if(isalnum(buf[i])){
              alpha_numeric_word = true;
          break;
       }        
    }
    if(alpha_numeric_word){
            temp = trim(buf);
            root = add_word(root, temp);
        alpha_numeric_word = false;
    }
    
    }

    free(buf);

    /*prints the results to file and stdout*/
    for (i = 0; i < 100; i++) {
        if (words_in_sentences[i] > 0) {
            printf("sentences of length %d: %d\n", i, words_in_sentences[i]);
            fprintf(out, "sentences of length %d: %d\n", i, words_in_sentences[i]);

        }
    }
    printf("sentences: %d\n", sentences);
    printf("words: %d\n", words);
    fprintf(out, "sentences: %d\n", sentences);
    fprintf(out, "words %d\n", words);
    print_words(root, out);
    free(words_in_sentences);
    destroy(root);    

}

