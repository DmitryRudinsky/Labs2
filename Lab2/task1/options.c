#include "options.h"
#include <stdio.h>
union m{

};
int strToUInt(char* str, unsigned* ans)
{
    if (str == NULL || ans == NULL || str[0] == '-') return invalidParams;

    unsigned res = 0;
    int add;
    for (int i = 0; str[i]; ++i)
    {
        if (str[i] < '0' || str[i] > '9') return invalidInput;
        add = str[i] - '0';
        if (res > (UINT_MAX - add) / 10) return overflow;

        res = res * 10 + add;
    }
    *ans = res;
    return ok;
}

int strLen(char* str)
{
    if (str == NULL) return -1;
    int ans = 0;
    --str;
    while (*(++str))
        ++ans;
    return ans;
}

int reverseStr(char* str, char** ans)
{
    if (str == NULL || ans == NULL) return invalidParams;

    int len = strLen(str);
    *ans = (char*) malloc((len + 1) * sizeof(char));
    if (*ans == NULL) return mallocError;

    (*ans)[len] = '\0';
    for(int i = 0; i < len; ++i)
    {
        (*ans)[len - 1 - i] = str[i];
    }
    return ok;
}

int upperCaseOdds(char* str, char** ans)
{
    if (str == NULL || ans == NULL) return invalidParams;

    int len = strLen(str);
    *ans = malloc((len + 1) * sizeof(char));
    if (*ans == NULL) return mallocError;

    for(int i = 0; i < len; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z') (*ans)[i] = str[i] + 'A' - 'a';
        else (*ans)[i] = str[i];
    }
    (*ans)[len] = '\0';

    return ok;
}

int nFunc(char* str, char** ans)
{
    if (str == NULL || ans == NULL) return invalidParams;

    int len = strLen(str);
    *ans = (char*) malloc((len + 1) * sizeof(char));
    if (*ans == NULL) return mallocError;

    char* buf = (char*) malloc((len) * sizeof(char));
    if (buf == NULL) {
        free(ans);
        return mallocError;
    }

    int numbers = 0, letters = 0, specs = 0;
    for(int i = 0; i < len; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            (*ans)[numbers] = str[i];
            ++numbers;
        }
        else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            buf[letters] = str[i];
            ++letters;
        }
        else
        {
            buf[len - specs - 1] = str[i];
            ++specs;
        }
    }

    for(int i = 0; i < letters; ++i) (*ans)[numbers + i] = buf[i];
    for(int i = 0; i < specs; ++i)
    {
        (*ans)[numbers + letters + i] = buf[len - 1 - i];
    }
    (*ans)[len] = '\0';

    free(buf);
    return ok;
}

int cFunc(char** str, int len, unsigned seed, char** ans)
{
    if (str == NULL || ans == NULL) return invalidParams;

    char** str_copy = (char**) malloc(len * sizeof(char*));
    if (str_copy == NULL) return mallocError;

    int char_sum = 0;
    for (int i = 0; i < len; ++i)
    {
        str_copy[i] = str[i];
        for(char* j = str[i]; *j; ++j)
        {
            ++char_sum;
        }
    }
    *ans = (char*) malloc((char_sum + 1) * sizeof(char));
    if(*ans == NULL) {
        free(str_copy);
        return mallocError;
    }

    srand(seed);
    int rand_index;
    char* ptr_in, *ptr_out = *ans;
    for (int i = len; i > 0; --i)
    {
        rand_index = rand() % i;
        ptr_in = str_copy[rand_index];
        while(*(ptr_in++))
            *(ptr_out++) = *(ptr_in - 1);
        str_copy[rand_index] = str_copy[i - 1];
    }
    *ptr_out = '\0';
    free(str_copy);
    return ok;
}
