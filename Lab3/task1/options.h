#ifndef OPTIONS_H
#define OPTIONS_H

typedef enum
{
    ok,
    incorrect_input,
    overflow,
    malloc_error,
    file_opening_error,
    file_reading_error,
    file_writing_error,
    wrong_way_error,
    unknown_error
} status_code;

extern const char* errors[];

status_code increment(int* n);
status_code decrement(int* n);
status_code str_to_int(char* in, int* out, int* neg);
status_code to_binbase_system(int n, int r, int** ans, int* length);

#endif // OPTIONS_H
