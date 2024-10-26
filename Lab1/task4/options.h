#ifndef TASK4_OPTIONS_H
#define TASK4_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

enum ValidationResult {
    VALIDATION_SUCCESS = 1,
    TOO_MANY_OR_TOO_FEW_ARGUMENTS = -3,
    INCORRECT_FLAG = 0,
    INCORRECT_FILE_INPUT = -1,
    INCORRECT_OUTPUT_FILE_INPUT = -2
};

int InFlags(char item);
int CheckValidation(int length, char *arguments[]);
void GenerateName(char new_name[], const char* name, int new_length, int length);
int IsLetter(char temp);
int IsDigit(char temp);
int FlagD(FILE* input, FILE* output);
int FlagI(FILE* input, FILE* output);
int FlagS(FILE* input, FILE* output);
int FlagA(FILE* input, FILE* output);

#endif // TASK4_OPTIONS_H
