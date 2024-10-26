#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "options.h"

const char* errors[] = {
        "Success\n",
        "Invalid input\n",
        "Invalid parameters were passed to the function\n",
        "The problem is unsolvable for the given arguments\n",
        "Overflow error\n",
        "Memory allocation error\n",
        "Cannot open the file\n",
        "Errors occurred while reading the file\n",
        "Errors occurred while writing to the file\n",
        "The contents of the file contradict the condition of the task\n",
        "Unknown error\n"
};

int charToDec(char n)
{
    if (n >= '0' && n <= '9') return n - '0';
    else if (n >= 'A' && n <= 'Z') return n - 'A' + 10;
    else if (n >= 'a' && n <= 'z') return n - 'a' + 10;
    return -1;
}

char decToChar(int base, int n)
{
    if (n >= 0 && n <= 9) return '0' + n;
    else if (n >= 10 && n <= 36) return 'A' - 10 + n;
    return 0;
}

StatusCode columnAddition(int base, char* l, char* r, char** ans)
{
    if (l == NULL || r == NULL || ans == NULL || base < 2 || base > 36) return INVALID_PARAMS;

    int maxLen = 0, minLen = 0, extraZero = 1;
    for (char* i = l; *i; ++i)
    {
        if (extraZero)
        {
            if (*i == '0')
            {
                ++l;
                continue;
            }
            extraZero = 0;
        }

        if (charToDec(*i) == -1) return INVALID_INPUT;
        ++maxLen;
    }
    extraZero = 1;
    for (char* i = r; *i; ++i)
    {
        if (extraZero)
        {
            if (*i == '0')
            {
                ++r;
                continue;
            }
            extraZero = 0;
        }
        if (charToDec(*i) == -1) return INVALID_INPUT;
        ++minLen;
    }
    if (minLen > maxLen)
    {
        char* charBuff = l;
        l = r;
        r = charBuff;
        int intBuff = maxLen;
        maxLen = minLen;
        minLen = intBuff;
    }

    *ans = (char*) malloc((maxLen + 2) * sizeof(char));
    if (*ans == NULL) return MALLOC_ERROR;
    int decSum, addToNext = 0;
    for (int i = 0; i < minLen; ++i)
    {
        decSum = charToDec(l[maxLen - 1 - i]) + charToDec(r[minLen - 1 - i]);
        decSum += addToNext;
        addToNext = 0;
        if (decSum >= base)
        {
            addToNext = 1;
            decSum -= base;
        }

        (*ans)[maxLen - i] = (decSum <= 9) ? ('0' + decSum) : ('A' + decSum - 10);
    }
    for (int i = minLen; i < maxLen; ++i)
    {
        decSum = charToDec(l[maxLen - 1 - i]) + addToNext;
        addToNext = 0;
        if (decSum >= base)
        {
            addToNext = 1;
            decSum -= base;
        }
        (*ans)[maxLen - i] = (decSum <= 9) ? ('0' + decSum) : ('A' + decSum - 10);
    }
    if (addToNext)
    {
        (*ans)[0] = '1';
    }
    else (*ans)[0] = '0';
    (*ans)[maxLen + 1] = '\0';
    return OK;
}

StatusCode someBaseSum(int base, char** ans, int n,...)
{
    if (ans == NULL || n < 2) return INVALID_PARAMS;

    va_list arg;
    va_start(arg, n);
    char* buff[2];
    StatusCode status = columnAddition(base, va_arg(arg, char*), va_arg(arg, char*), buff);
    if (status != OK)
    {
        va_end(arg);
        return status;
    }
    int i = 2;
    for (; i < n; ++i)
    {
        status = columnAddition(base, buff[i % 2], va_arg(arg, char*), buff - i % 2 + 1);
        if (status != OK)
        {
            va_end(arg);
            if (i > 2) free(buff[1]);
            free(buff[0]);
            return status;
        }
    }
    *ans = buff[i % 2];
    if (i > 2) free(buff[1 - i % 2]);
    if ((*ans)[0] == '0' && (*ans)[1] != '\0')
    {
        i = 0;
        do
        {
            ++i;
            (*ans)[i-1] = (*ans)[i];
        } while ((*ans)[i-1]);
        buff[0] = (char*) realloc(*ans, sizeof(char) * i);
        if (buff[0] == NULL)
        {
            free(*ans);
            return MALLOC_ERROR;
        }
    }
    va_end(arg);
    return OK;
}
