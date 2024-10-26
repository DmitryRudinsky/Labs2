#ifndef TASK9_OPTIONS_H
#define TASK9_OPTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>


#define ll long long
#define ull unsigned long long
#define eps 1e-15
typedef enum
{
    ok,
    invalid_input,
    invalid_params,
    weird_values,
    overflow,
    malloc_error,
    file_opening_error,
    file_reading_error,
    file_writing_error,
    file_invalid_data,
    unknown_error
}status_code;

static const char* errors[] =
        {
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

status_code searchFiniteRepr(int base, ull mantissa, int power10, int* ans);
status_code polySearchFiniteReprs(int base, int** ans, int n, ...);

#endif //TASK9_OPTIONS_H
