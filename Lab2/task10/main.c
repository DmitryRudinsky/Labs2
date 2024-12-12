#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

typedef enum {
    SUCCESS,
    INCORRECT_OPTIONS_ERROR,
    MEMORY_ALLOCATED_ERROR,
    OVERFLOW_ERROR
} error_msg;

long long int special_product(int n, int p);
long long int fac(int x);

error_msg DecompositionPolynomial(double eps, double a, double **result, int n, ...) {
    if (eps < 1e-40) return INCORRECT_OPTIONS_ERROR;
    va_list factor;
    va_start(factor, n);
    *result = (double *)calloc(n + 1, sizeof(double));
    double * tmp_result = *result;
    double coefficients[n + 1];
    if (!*result) {
        va_end(factor);
        return MEMORY_ALLOCATED_ERROR;
    }
    double x;
    for (int i = 0; i <= n; ++i) {
        x = va_arg(factor, double);
        coefficients[i] = x;
    }
    tmp_result[n] = coefficients[n];
    for (int i = n - 1, count_derivative = n - 1; i >= 0; --i, count_derivative--) {
        for (int j = i, k = 0; j <= n; ++j, ++k) {
            if ((fabsl((long double)special_product(count_derivative, j) * coefficients[j]) * pow(a, k) -
                 (long double)DBL_MAX) >= eps)
                return OVERFLOW_ERROR;
            tmp_result[i] += (double)special_product(count_derivative, j) * coefficients[j] * pow(a, k);
        }
        tmp_result[i] /= (double)fac(i);
    }
    return SUCCESS;
}

int compare(double a, double b, double eps) {
    if ((a - b) >= eps) return 1;
    if ((b - a) >= eps) return -1;
    return 0;
}

long long int special_product(int n, int p) {
    long long int x = 1;
    for (int i = 0; i < n; ++i) {
        x *= p;
        p -= 1;
    }
    return x;
}

long long int fac(int x) {
    long long int s = 1;
    for (int i = 2; i <= x; ++i) {
        s *= i;
    }
    return s;
}

void print_error(error_msg error) {
    switch (error) {
        case SUCCESS:
            printf("Success\n");
            break;
        case INCORRECT_OPTIONS_ERROR:
            printf("Incorrect options error\n");
            break;
        case MEMORY_ALLOCATED_ERROR:
            printf("Memory allocated error\n");
            break;
        case OVERFLOW_ERROR:
            printf("Overflow error\n");
            break;
    }
}

int main(){
    double *res;
    error_msg errorMsg = DecompositionPolynomial(1e-4, 3, &res, 4, -2.0, 1.0, -3.0, 0.0, 1.0);
    if(errorMsg) {
        print_error(errorMsg);
        return 1;
    }
    for(int i = 0; i < 5;++i){
        printf("%f ", res[i]);
    }
    printf("\n");
    free(res);
    return 0;
}