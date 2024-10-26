#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

status_code solveDichotomy(double l, double r, double eps, double (*func)(double), double* ans);
double testFunc1(double x);
double testFunc2(double x);
double testFunc3(double x);
double testFunc4(double x);