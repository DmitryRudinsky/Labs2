#include <stdio.h>
#include <stdlib.h>
#include "options.h"

int main(int argc, char** argv)
{
    StatusCode status;
    char* ans;
    status = someBaseSum(2, &ans, 4, "0", "1000", "100", "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    if (status != OK)
    {
        printf("%s", errors[status]);
        return status;
    }
    printf("%s\n", ans);
    free(ans);
    return 0;
}
