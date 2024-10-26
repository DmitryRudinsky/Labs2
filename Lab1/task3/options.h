#ifndef TASK3_OPTIONS_H
#define TASK3_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

int FlagValidation(char *flag);
int ArgumentsAmountValidation(char flag, int argc);
int RealNumberValidation(char *number);
int IntegerNumberValidation(char *number);
int Triangle(double a, double b, double c, double epsilon);
void Swap(double *coefficients, int i, int j);
int Permutations(double *coefficients, int amount, double epsilon);
int EquationsRoots(double *roots, double *coefficients, double epsilon);
int Comp(const double *num1, const double *num2);
double MyAtof(const char* arr);
int MyAtoi(char* str);

#endif // TASK3_OPTIONS_H
