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

    int buffer_size = 8;
    *ans = (int*) malloc(buffer_size * sizeof(int));
    if (*ans == NULL) {
        return malloc_error;
    }

    int mask = (1 << r) - 1;
    *length = 0;

    while (n != 0) {
        if (*length >= buffer_size) {
            buffer_size *= 2;
            int* new_ans = (int*) realloc(*ans, buffer_size * sizeof(int));
            if (new_ans == NULL) {
                free(*ans);
                return malloc_error;
            }
            *ans = new_ans;
        }

        (*ans)[*length] = n & mask;
        n >>= r;
        (*length)++;
    }

    for (int i = 0; i < *length / 2; i++) {
        int temp = (*ans)[i];
        (*ans)[i] = (*ans)[*length - i - 1];
        (*ans)[*length - i - 1] = temp;
    }

    return ok;
}

