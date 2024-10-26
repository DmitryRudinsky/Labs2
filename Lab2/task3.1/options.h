#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum{
    string_ok = 0,
    string_allocation_error = -1,
} status;

typedef struct{
    char* file;
    int string;
    int symbol;
} answer;

status substrings_function(answer** result, int* substrings_amount, const char* substring, const int file_amount, ...);