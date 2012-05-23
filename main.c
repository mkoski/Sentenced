/*
 * This file contains main-function which opens the file streams, parses 
 * the command line arguments
 * and calls for functions according to them. 
 * File has function int main(int argc, char *argv[])
 * File calls functions help(), info() and error() from misc.c, 
 * run_test() from tests.c, read_words(FILE*, FILE*) from read.c
 * Author : MK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "sentenced.h"

/*
 * The functionality of this function is explained in the main comment. 
 * Parameters int argc, char *argv[]  (commad line arguments)
 * Returns int (exit-value) 
 */
int main(int argc, char *argv[]) {

    FILE* in;
    FILE* out;
    char* resource;
    char* result = "results.txt";
    bool read_stdin = false;
    bool in_checked = false;
    bool out_checked = false;
    int i;
    if (argc < 2){
        run_test(); /* comment this line if you don't want to run tests*/
        info();
    }
    if (argc > 3) {
        error(1);
        info();
    }

    /*Check the arguments*/
    for (i = 1; i < argc && i < 3; i++) {
        char * s = argv[i];
        if (s[0] == '-') {
            switch (s[1]) {
                case 'h':
                    if (in_checked || out_checked || read_stdin)
                        error(2);
                    help();
                case 'i':
                    if (!in_checked) {
                        resource = &argv[i][2];
                        read_stdin = false;
                        in_checked = true;
                        break;
                    } else {
                        error(2);
                        info();
                    }
                case 'o':
                    if (!out_checked) {
                        result = &argv[i][2];
                        out_checked = true;
                        break;
                    } else {
                        error(2);
                        info();
                    }
                case 's':
                    if (!in_checked) {
                        in_checked = false;
                        read_stdin = true;
                        break;
                    } else {
                        error(2);
                        info();
                    }
                default:
                    info();
                    break;
            }
        }
    }

    /*Open file for output*/
    if ((out = fopen(result, "w")) == NULL) {
        fprintf(stderr, "Cannot write to output file %s!\n.", result);
        return 1;
    }
    /*Read words from stdin*/
    if (read_stdin) {
        read_words(stdin, out);
        fclose(out);
    } else /*Read from file*/
        if ((in = fopen(resource, "r")) == NULL) {
        fprintf(stderr, "Cannot open input file %s!\n.", resource);
        return 1;
    } else {
        read_words(in, out);
        fclose(in);
        fclose(out);
    }
    return (EXIT_SUCCESS);
}