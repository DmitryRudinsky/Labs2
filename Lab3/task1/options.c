#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

const char* errors[] = {
        "Success\n",
        "Invalid input\n",
        "Overflow error\n",
        "Memory allocation error\n",
        "Cannot open file\n",
        "Cannot read file correctly\n",
        "Writing to file error\n",
        "Wrong way to file\n",
        "Unknown error\n"
};

status_code increment(int* n) {
    if (n == NULL) return incorrect_input;
    int mask = 1;
    while (*n & mask)
    {
        *n ^= mask;
        mask <<= 1;
    }
    *n |= mask;

    return ok;
}

status_code decrement(int* n) {
    if (n == NULL) return incorrect_input;
    int mask = 1;
    while (~(*n) & mask)
    {
        *n |= mask;
        mask <<= 1;
    }
    *n ^= mask;

    return ok;
}

status_code str_to_int(char* in, int* out, int* neg) {
    if (in == NULL || out == NULL || neg == NULL) {
        return incorrect_input;
    }
    if (in[0] == '-') {
        *neg = 1;
        ++in;
    } else {
        *neg = 0;
    }

    errno = 0;
    char* end = NULL;
    *out = strtol(in, &end, 10);
    if (errno == ERANGE)
        return overflow;

    if (errno != 0 && *out == 0)
        return unknown_error;

    if (in == end || *end != '\0')
        return incorrect_input;

    return ok;
}


status_code to_binbase_system(int n, int r, int** ans, int* length) {
    if (ans == NULL || length == NULL) return incorrect_input;
    if (n == 0) {
        *ans = (int*) malloc(sizeof(char));
        if (*ans == NULL)
        {
            return malloc_error;
        }
        **ans = '0';
        *length = 1;
        return ok;
    }

    *ans = (int*) malloc(8 * sizeof(n));
    if (*ans == NULL) {
        return malloc_error;
    }

    int mask = 1;
    for (int i = 1; i < r; increment(&i)) {
        mask <<= 1;
        increment(&mask);
    }

    *length = 0;
    while (n != 0) {
        (*ans)[*length] = (n & mask);
        n >>= r;
        increment(length);
    }

    int i = *length - 1;
    int j = 0;
    while (i > j) {
        mask = (*ans)[i];
        (*ans)[i] = (*ans)[j];
        (*ans)[j] = mask;
        decrement(&i);
        increment(&j);
    }
    return ok;
}
