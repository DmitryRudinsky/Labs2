#include "options.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("%s", errors[invalidInput]);
        return invalidInput;
    }

    if (strLen(argv[1]) != 2 || argv[1][0] != '-')
    {
        printf("%s", errors[invalidInput]);
        return invalidInput;
    }

    if (argv[1][1] != 'c' && argc != 3)
    {
        printf("%s", errors[invalidInput]);
        return invalidInput;
    }

    int status;
    switch (argv[1][1])
    {
        case 'l':
            printf("%d\n", strLen(argv[2]));
            break;

        case 'r':
        {
            char* ans;
            status = reverseStr(argv[2], &ans);
            if (status != ok) break;
            for(char* i = ans; *i; ++i)
            {
                printf("%c", *i);
            }
            printf("\n");
            free(ans);
            break;
        }
        case 'u':
        {
            char* ans;
            status = upperCaseOdds(argv[2], &ans);
            if (status != ok) break;
            for(char* i = ans; *i; ++i)
            {
                printf("%c", *i);
            }
            printf("\n");
            free(ans);
            break;
        }
        case 'n':
        {
            char* ans;
            status = nFunc(argv[2], &ans);
            if (status != ok) break;
            for(char* i = ans; *i; ++i)
            {
                printf("%c", *i);
            }
            printf("\n");
            free(ans);
            break;
        }
        case 'c':
        {
            if (argc < 5)
            {
                printf("%s", errors[invalidInput]);
                return invalidInput;
            }
            unsigned seed;
            if (argv[3][0] == '-')
            {
                printf("%s", errors[invalidInput]);
                return invalidInput;
            }
            status = strToUInt(argv[3], &seed);
            if (status != ok) break;
            char** str = (char**) malloc((argc - 3) * sizeof(char*));
            if (str == NULL)
            {
                printf("%s", errors[mallocError]);
                return mallocError;
            }
            str[0] = argv[2];
            for(int i = argc - 4; i > 0; --i)
            {
                str[i] = argv[i + 3];
            }
            char* ans;
            status = cFunc(str, argc - 3, seed, &ans);
            free(str);
            if (status != ok) break;
            for(int i = 0; ans[i]; ++i)
            {
                printf("%c", ans[i]);
            }
            printf("\n");
            free(ans);
            break;
        }
        default:
            printf("%s", errors[invalidInput]);
            break;
    }
    printf("%s", errors[status]);
    return status;
}
