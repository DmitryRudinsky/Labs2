#ifndef TASK8_OPTIONS_H
#define TASK8_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define N 10
#define MAX_WORD_LENGTH 100

int IsDigit(char temp);
int IsAlpha(char symbol);
void InputError();
int IsDelimiter(char symbol);
long long GetDecimalNumber(char *number, int base, int flag);
int GetMinBase(char *number, int flag);
int CheckWord(char *word);
void ProcessFile(FILE *input, FILE *output);

#endif //TASK8_OPTIONS_H
