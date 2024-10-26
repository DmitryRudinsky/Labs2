#include "options.h"

int main()
{
    int* ans;
    int n = 3;
    status_code status = polySearchFiniteReprs(8, &ans, n, 0.125, 0.5, 0.04);
    if (status != ok)
    {
        printf("%s", errors[status]);
        return status;
    }
    for(int i = 0; i < n; ++i)
    {
        printf("%d. ", i+1);
        if (ans[i]) printf("yes\n");
        else printf("no\n");
    }
    free(ans);
    return 0;
}