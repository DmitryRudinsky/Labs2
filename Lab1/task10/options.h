#ifndef TASK10_OPTIONS_H
#define TASK10_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define N 256

enum ERRORS {
    kSuccess = 0,
    kIncorrectInput = -1,
    kIncorrectConsoleInput = -2,
    kOneElementArray = -3,
    kNoMemory = -4
};

int MyAtoi(char* str);
void ShowMenu(int state);
void PrintError(int error);
int IsDigit(char *number);
int BaseValidCheck(char *base);
int NumberCheckValid(char *number, int base);
int GetDecimalNumber(char *number, int base);
int ToBase(char **buf, int size, int number, int base);
int GetLength(int number, int base);
int GetString(char **string);

#endif //TASK10_OPTIONS_H
