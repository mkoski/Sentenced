/*
 * This file contains miscellaneous functions which are called from main.c.
 * These functions open readme-file and print it to stdout, print options usage
 * -info and handle error when too many or few arguments are given as command 
 * line arguments.
 * File contains functions: void help(void), void info(void), 
 * void error(int err_code).  
 * Author: MK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "sentenced.h"

/*
 * This function prints the readme-file to stdout
 * Returns int (exit-code)
 */
void help(void) {
    FILE* readme;
    char* file_name = "README";
    char c;
    if (( readme = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "Cannot open README file\n.");
        info();
        exit (0);
    }
    else {
        while( (c = fgetc(readme)) != EOF) {
            fputc(c,stdout);
        }
    }
    fclose(readme);
    exit(0);
}

/*
 * This function prints the option usage -info to stdout
 * Returns int (exit-code)
 */
void info(void) {
    fopen("README", "r");
    printf("Usage:\n");
    printf("\t-h\t");
    printf("\tprint the README file\n");
    printf("\t-s\t");
    printf("\tread words from command line, <ctrl> + d quits\n");
    printf("\t-i<filename>\t");
    printf("read words from  the file <filename>\n");
    printf("\t-o<filename>\t");
    printf("print results to the file <filename> (default is results.txt)\n");
    exit(0);
}

/*
 * This method prints error messages according to error code.
 * Parameter: int err_code (err_code)
 * Returns int (exit-code)
 */
void error(int err_code) {
    if (err_code == 1)
        printf("Too many arguments!\n");
    if (err_code == 2)
        printf("Illegal arguments!\n");
    exit(0);
}
