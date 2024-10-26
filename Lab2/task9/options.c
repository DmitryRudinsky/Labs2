#include "options.h"

status_code searchFiniteRepr(int base, ull mantissa, int power10, int* ans)
{
    if (ans == NULL || base < 2) return invalid_params;

    int power2 = power10, power5 = power10;

    while(power2 && !(mantissa % 2))
    {
        mantissa /= 2;
        --power2;
    }

    while(power5 && !(mantissa % 5))
    {
        mantissa /= 5;
        --power5;
    }
    if(power2 && (base % 2) || power5 && (base % 5)) *ans = 0;
    else *ans = 1;
    return ok;
}

status_code polySearchFiniteReprs(int base, int** ans, int n, ...)
{
    if (ans == NULL) return invalid_params;

    va_list arg;
    va_start(arg, n);

    *ans = (int*) malloc(sizeof(int) * n);
    if (*ans == NULL)
    {
        va_end(arg);
        return malloc_error;
    }

    double eps_opposite = 1, frac;
    ull power10 = 0;
    status_code status;

    while (1.0 / eps_opposite > eps)
    {
        if (ULLONG_MAX / 10 < eps_opposite) return overflow;
        eps_opposite *= 10;
        ++power10;
    }

    for(int i = 0; i < n; ++i)
    {
        frac = va_arg(arg, double);
        if (frac > 1)
        {
            free(*ans);
            va_end(arg);
            return invalid_input;
        }
        status = searchFiniteRepr(base, eps_opposite*frac, power10, *ans + i);
        if (status != ok)
        {
            free(*ans);
            va_end(arg);
            return status;
        }
    }
    va_end(arg);
    return ok;
}