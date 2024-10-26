#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>
#include <limits.h>

typedef enum
{
    ok,
    invalidInput,
    invalidParams,
    weirdValues,
    overflow,
    mallocError,
    fileOpeningError,
    fileReadingError,
    fileWritingError,
    fileInvalidData,
    unknownError
} statusCode;

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

int strToUInt(char* str, unsigned* ans);
int strLen(char* str);
int reverseStr(char* str, char** ans);
int upperCaseOdds(char* str, char** ans);
int nFunc(char* str, char** ans);
int cFunc(char** str, int len, unsigned seed, char** ans);

#endif // OPTIONS_H
