#ifndef TASK2_OPTIONS_H
#define TASK2_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

#define PI 3.14

double MyAtof(const char* arr);
int MyAtoi(char* str);
int IsPositiveDigit(char *number);
int IsDouble(char *number);
int IsEpsilonRepresentation(char *eps);
int CheckIsEpsilon(char *eps);
double Factorial(double number);
double FindELimit(double eps);
double FindERow(double eps);
double FindEFunction(double eps);
double FindPiLimit(double eps);
double FindPiRow(double eps);
double FindPiFunction(double eps);
double FindLn2Limit(double eps);
double FindLn2Row(double eps);
double FindLn2Function(double eps);
double FindSqrt2Limit(double eps);
double FindSqrt2Row(double eps);
double FindSqrt2Function(double eps);
double FindC(double n, double k);
double FindGammaLimit(double eps);
double FindGammaRow(double eps);
int CheckPrime(int number);
double PForGamma(int t);
double LimitForGamma(double eps);
double FindGammaFunction(double eps);
void Menu();

#endif // TASK2_OPTIONS_H
