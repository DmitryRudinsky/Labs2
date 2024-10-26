#ifndef TASK1_OPTIONS_H
#define TASK1_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

enum ERRORS {
    success = 0,
    incorrect_input = -1,
    file_error = -2,
    no_memory = -3,
    fail = -4
};

int findSubstringInFiles(char *substring, char **answer, int quantity, ...);
int appendToAnswer(char **answer, int length, int file_count, int **result, int count);
int appendString(char **answer, int *length, char *string);
int findSubstring(int ***result, char *substring, FILE* file);
int checkString(char *substring, char *string);
int changeBuffer(char buffer[], FILE *file, int length);
void printError(int error);

#endif //TASK1_OPTIONS_H
