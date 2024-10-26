#include "options.h"


double MyAtof(const char* arr) {
    double val = 0;
    int after_dot = 0;
    double scale = 1;
    int neg = 0;

    if (*arr == '-') {
        arr++;
        neg = 1;
    }

    while (*arr) {
        if (after_dot) {
            scale /= 10;
            val += (*arr - '0') * scale;
        } else {
            if (*arr == '.') {
                after_dot++;
            } else {
                val = val * 10.0 + (*arr - '0');
            }
        }
        arr++;
    }

    return neg ? -val : val;
}

int IsDouble(const char* number) {
    int decimal_point_count = 0;
    if (*number == '-') return 0;

    while (*number != '\0') {
        if (*number == '.') {
            if (decimal_point_count == 0) {
                decimal_point_count++;
            } else {
                return 0;
            }
        } else if (!(*number >= '0' && *number <= '9')) {
            return 0;
        }
        number++;
    }
    return 1;
}

int IsEpsilonRepresentation(const char* eps) {
    int length = strlen(eps);
    if (length < 4) return 0;
    if (eps[0] != '1' || eps[1] != 'e' || eps[2] != '-') {
        return 0;
    }

    for (int i = 3; i < length; ++i) {
        if (!(eps[i] >= '0' && eps[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

int CheckIsEpsilon(const char* eps) {
    if (IsDouble(eps)) {
        return 1;
    }
    if (IsEpsilonRepresentation(eps)) {
        return 1;
    }
    return 0;
}

double FunctionA(double x) {
    return log(1 + x) / x;
}

double FunctionB(double x) {
    return exp(-0.5 * x * x);
}

double FunctionC(double x) {
    return log(1.0 / (1.0 - x));
}

double FunctionD(double x) {
    return pow(x, x);
}

double IntegralA(double eps) { //Метод Симпсона
    double a = 0, b = 1.0, square = 0;
    double h = (b - a) * eps;
    double x = a + h;

    while (x - b < eps) {
        square += 4.0 * FunctionA(x);
        x += h;
        if (x - b >= eps) {
            break;
        }
        square += 2.0 * FunctionA(x);
        x += h;
    }
    square = (h / 3.0) * (square + FunctionA(b));
    return square;
}

double IntegralB(double eps) {
    double a = 0, b = 1.0, square = 0;
    double h = (b - a) * eps;
    double x = a + h;

    while (x - b < eps) {
        square += 4 * FunctionB(x);
        x += h;
        if (x - b >= eps) {
            break;
        }
        square += 2 * FunctionB(x);
        x += h;
    }
    square = (h / 3.0) * (square + 1.0 + exp(-0.5));
    return square;
}

double IntegralC(double eps) {
    double a = 0, b = 1.0, square = 0;
    double h = (b - a) * eps;
    double x = a + h;

    while (x < b) {
        square += 4 * FunctionC(x);
        x += h;
        if (x >= b) {
            break;
        }
        square += 2 * FunctionC(x);
        x += h;
    }
    square = (h / 3.0) * square;
    return square;
}

double IntegralD(double eps) {
    double a = 0, b = 1.0, square = 0;
    double h = (b - a) * eps;
    double x = a + h;

    while (x - b < eps) {
        square += 4 * FunctionD(x);
        x += h;
        if (x - b >= eps) {
            break;
        }
        square += 2 * FunctionD(x);
        x += h;
    }
    square = (h / 3.0) * (square + 2.0);
    return square;
}