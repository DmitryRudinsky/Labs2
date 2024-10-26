#include "options.h"
const double kEpsilon = 0.000001;

int main()
{
    double ans, eps = 0.000001;
    int status = solveDichotomy(-1, 1, eps, testFunc1, &ans);
    printf("1. ");
    if (status)
    {
        printf("%s", errors[status]);
    }
    else printf("%lf\n", ans);
    printf("2. ");
    status = solveDichotomy(-10, 10, eps, testFunc2, &ans);
    if (status)
    {
        printf("%s", errors[status]);
    }
    else printf("%lf\n", ans);
    printf("3. ");
    status = solveDichotomy(-1, 4, eps, testFunc3, &ans);
    if (status)
    {
        printf("%s", errors[status]);
    }
    else printf("%lf\n", ans);
    printf("4. ");
    status = solveDichotomy(-1, 4, eps, testFunc4, &ans);
    if (status)
    {
        printf("%s", errors[status]);
    }
    else printf("%lf\n", ans);

    return 0;
}
