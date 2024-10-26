#include <stdio.h>
#include <stdarg.h>
#include "options.h"

status_code calculate_polynomial(double x, int coef_num, double* coefs, double* ans)
{
    if (coefs == NULL || ans == NULL) return invalid_params;

    *ans = 0;
    for(int i = coef_num - 1; i >= 0; --i)
    {
        *ans *= x;
        *ans += coefs[i];
    }
    return ok;
}

status_code transform_polynomial(double eps, double a, double** ans, int n, ...)
{
    if (ans == NULL) return invalid_params;

    double* coefs = (double*) malloc(n * sizeof(double));
    if (coefs == NULL) return malloc_error;
    *ans = (double*) malloc(n * sizeof(double));
    if (*ans == NULL)
    {
        free(coefs);
        return malloc_error;
    }

    va_list arg;
    va_start(arg, n);
    for(int i = 0; i < n; ++i)
    {
        coefs[i] = va_arg(arg, double);
    }
    va_end(arg);

    status_code status;
    unsigned long long fact = 1;
    for(int i = 0; i < n; ++i)
    {
        status = calculate_polynomial(a, n - i, coefs, *ans + i);
        if (status != ok)
        {
            free(coefs);
            free(*ans);
            return status;
        }

        (*ans)[i] /= fact;
        fact *= i + 1;

        for(int j = 0; j < n - 1 - i; ++j)
        {
            coefs[j] = (j + 1) * coefs[j + 1];
        }
        coefs[n - i - 1] = 0;
    }

    free(coefs);
    return ok;
}
