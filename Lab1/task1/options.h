#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef enum Options {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F,
    OPT_INVALID
} Options;

typedef enum {
    OPT_SUCCESS = 0,
    OPT_INVALID_NUMBER = -1,
    OPT_UNKNOWN_OPTION = -2,
    OPT_INVALID_ARGUMENTS = -3
} OptError;


int MyAtoi(char* str);
bool IsNumber(const char* str);
void PrintError(int error);
bool IsPrime(int num);
long long Factorial(int num);
int SumNaturalNumbers(int x);
void PrintMultiples(int x);
void SplitIntoHexDigits(int x);
void PrintPowerTable(int x);
int GetOpts(int argc, char** argv, Options *option, int *number);
void HandleOptH(int number);
void HandleOptP(int number);
void HandleOptS(int number);
void HandleOptE(int number);
void HandleOptA(int number);
void HandleOptF(int number);

#endif // OPTIONS_H
