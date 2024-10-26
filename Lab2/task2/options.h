#ifndef TASK1_OPTIONS_H
#define TASK1_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

enum ErrorCode {
    kErrorNone = 0,
    kErrorNegativeProduct
};
typedef enum ErrorCode ErrorCode;

double MyPow(double base, int power);
double GeometricAverage(ErrorCode *error, int amount, ...);


#endif //TASK1_OPTIONS_H
