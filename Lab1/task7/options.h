#ifndef TASK7_OPTIONS_H
#define TASK7_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR_FLAG 1
#define ERROR_ARG_COUNT 2
#define ERROR_FILE 3

int TenToFour(char symbol);
int TenToEight(char symbol);
void ProcessRMode(FILE *file1, FILE *file2, FILE *file3);
void ProcessAMode(FILE *file1, FILE *file2);
int ValidateFlag(char *flag);
int ValidateArgCount(int argc, char flag);


#endif //TASK7_OPTIONS_H
