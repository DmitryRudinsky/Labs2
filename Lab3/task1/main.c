#include "options.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 3)
    {
        printf("%s", errors[incorrect_input]);
        return 1;
    }

    int* ans;
    int len, neg;

    int base;
    if (str_to_int(argv[2], &base, &neg) != ok || base < 1 || base > 5)
    {
        printf("%s", errors[incorrect_input]);
        return 1;
    }

    int number;
    if (str_to_int(argv[1], &number, &neg) != ok)
    {
        printf("%s", errors[incorrect_input]);
        return 1;
    }

    to_binbase_system(number, base, &ans, &len);
    if (neg) printf("-");
    for (int i = 0; i < len; increment(&i))
    {
        printf("%d", ans[i]);
    }
    printf("\n");

    free(ans);
    return 0;
}
