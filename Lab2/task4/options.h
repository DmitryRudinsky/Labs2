#ifndef TASK1_OPTIONS_H
#define TASK1_OPTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>



enum status{
    convex = 1,
    not_convex = 0,
    too_few_arguments = -1,

};

double polynomialCalculator(double point, int power, ...);
int signFunc(double x);
int convexPolygon(int amount, ...);
bool isKaprekar(unsigned long long n, int base);
void findKaprekarNumbers(int base, int count, ...);


#endif //TASK1_OPTIONS_H
