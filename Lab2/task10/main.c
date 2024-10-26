#include <stdio.h>
#include "options.h"

int main()
{
    double* coefs;
    int n = 3;
    status_code status = transform_polynomial(0.000001, 4, &coefs, n, 1.0, 3.0, 2.0);
    if (status != ok)
    {
        printf("%s", errors[status]);
        return status;
    }

    for (int i = 0; i < n; ++i)
    {
        printf("g%d = %lf\n", i, coefs[i]);
    }

    free(coefs);
    return 0;
}
