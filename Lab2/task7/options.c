#include "options.h"


status_code solveDichotomy(double l, double r, double eps, double (*func)(double), double* ans)
{
    if (func == NULL || ans == NULL || eps <= 0 || r < l) return invalid_params;

    if (func(r) * func(l) > 0) return weird_values;
    if (fabs(func(r)) < eps)
    {
        *ans = r;
        return ok;
    }
    if (fabs(func(l)) < eps)
    {
        *ans = l;
        return ok;
    }

    double mid, val;
    do
    {
        mid = (l + r) / 2;
        val = func(mid);
        if (val * func(r) > 0) r = mid;
        else l = mid;
    } while (fabs(val) > eps);

    *ans = mid;
    return ok;
}

double testFunc1(double x) {
    return x;
}

double testFunc2(double x) {
    return x + 3;
}

double testFunc3(double x) {
    return x * x - 4 * x + 3;
}

double testFunc4(double x) {
    return x * x - 4;
}