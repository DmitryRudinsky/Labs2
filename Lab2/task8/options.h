#ifndef OPTIONS_H
#define OPTIONS_H

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_PARAMS,
    WEIRD_VALUES,
    OVERFLOW,
    MALLOC_ERROR,
    FILE_OPENING_ERROR,
    FILE_READING_ERROR,
    FILE_WRITING_ERROR,
    FILE_INVALID_DATA,
    UNKNOWN_ERROR
} StatusCode;

extern const char* errors[];

int charToDec(char n);
char decToChar(int base, int n);
StatusCode columnAddition(int base, char* l, char* r, char** ans);
StatusCode someBaseSum(int base, char** ans, int n,...);

#endif
