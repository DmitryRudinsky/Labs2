#include "options.h"

double SummA(double epsilon, double x) {
    double sum = 1 + x;
    int n = 2;
    double elem = x, elem_prev;

    do {
        elem_prev = elem;
        elem *= x / n;
        if (fabs(n - x) < epsilon) {
            elem_prev = 0;
        }
        n++;
        sum += elem;
    } while (fabs(elem - elem_prev) > epsilon);

    return sum;
}

double SummB(double epsilon, double x) {
    double sum = 1;
    int n = 1;
    double elem = 1, elem_prev;

    do {
        elem_prev = elem;
        elem *= -(x * x / (4 * n * n - 2 * n));
        n++;
        sum += elem;
    } while (fabs(elem - elem_prev) > epsilon);

    return sum;
}

double SummC(double epsilon, double x) {
    double sum = 1;
    int n = 1;
    double elem = 1, elem_prev;

    do {
        elem_prev = elem;
        elem *= 9 * n * n * x * x / (9 * n * n - 9 * n + 2);
        n++;
        sum += elem;
    } while (fabs(elem - elem_prev) > epsilon);

    return sum;
}

double SummD(double epsilon, double x) {
    double sum = -x * x / 2;
    int n = 2;
    double elem = -x * x / 2, elem_prev;

    do {
        elem_prev = elem;
        elem *= -((2 * n - 1) * x * x) / (2 * n);
        n++;
        sum += elem;
    } while (fabs(elem - elem_prev) > epsilon);

    return sum;
}

int IsDouble(const char* number) {
    int dot_count = 0;

    if (*number == '-') return 0;

    while (*number != '\0') {
        if (*number == '.') {
            if (dot_count == 0) {
                dot_count++;
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
