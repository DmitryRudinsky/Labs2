#include "options.h"
#define MAX(a, b) (a > b ? a : b)

double MyPow(double base, int power) {
    if (power < 0) {
        base = 1.0 / base;
        power = abs(power);
    }

    if (power == 0) {
        return 1;
    }

    if (power % 2 == 1) {
        return MyPow(base, power - 1) * base;
    } else {
        double result = MyPow(base, power / 2);
        return result * result;
    }
}

double GeometricAverage(ErrorCode *error, int amount, ...) {
    double result = 1.0;
    va_list numbers;

    va_start(numbers, amount);
    for (int i = 0; i < amount; ++i) {
        result *= va_arg(numbers, double);
    }
    va_end(numbers);

    if (amount % 2 == 0 && result < 0) {
        if (error != NULL) {
            *error = kErrorNegativeProduct;
        }
        return -1.0;
    }

    result = pow(result, 1.0 / amount);

    if (error != NULL) {
        *error = kErrorNone;
    }

    return result;
}