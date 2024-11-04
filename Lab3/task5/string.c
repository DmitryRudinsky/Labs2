#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2
};

enum COMPARISON
{
    identical = 0,
    more = 1,
    less = -1
};

// создание строки
String_ptr create_string(const char * buffer)
{
    String_ptr string = (String_ptr) malloc(sizeof(String));
    if (!string) return NULL;
    string -> length = strlen(buffer);
    string -> buffer = (char*) malloc((string -> length + 1) * sizeof(char));
    if (!(string -> buffer))
    {
        free(string);
        string = NULL;
        return NULL;
    }
    strcpy(string -> buffer, buffer);
    return string;
}

// удаление строки
void delete_string(String_ptr string)
{
    if (!string) return;
    if (string -> buffer)
    {
        free(string -> buffer);
        string -> buffer = NULL;
    }
    free(string);
    string = NULL;
}

// отношение порядка
// 0 - если и
// 1 - если 1 больше
// -1 если 2 больше
int strings_order_relation(const String_ptr first, const String_ptr second)
{
    if (first -> length > second -> length) return more;
    else if (first -> length < second -> length) return less;

    int length = first -> length;
    for (int i = 0; i < length; ++i)
    {
        if ((first -> buffer)[i] > (second -> buffer)[i]) return more;
        if ((second -> buffer)[i] > (first -> buffer)[i]) return less;
    }
    return identical;
}

// отношение эквивалентности
int strings_cmp(const String_ptr first, const String_ptr second)
{
    if (first -> length != second -> length) return fail;

    int length = first -> length;
    for (int i = 0; i < length; ++i)
    {
        if ((first -> buffer)[i] != (second -> buffer)[i]) return fail;
    }
    return success;
}

//копирование
void strings_copy(const String_ptr from, String_ptr to)
{
    to -> length = from -> length;
    strcpy(to -> buffer, from -> buffer);
    return;
}

// дублирование строки
String_ptr dublicate(const String_ptr string)
{
    String_ptr new_string = create_string(string -> buffer);
    if (!new_string) return NULL;
    return new_string;
}

int string_copy_dynamic(String_ptr new_string, const String_ptr string)
{
    if (!new_string) return fail; // динамическая память не выделена
    new_string -> length = string -> length;
    new_string -> buffer = (char*) malloc((new_string -> length) * sizeof(char));
    if (!(new_string -> buffer)) return no_memory;
    memcpy(new_string -> buffer, string -> buffer, string -> length);
    return success;
}

// объединяет две строки в одну новую
String_ptr concatenation(const String_ptr first, const String_ptr second)
{
    char * buffer = (char*)malloc(((first -> length) + (second -> length) + 1) * sizeof(char));
    if (!buffer) return NULL;

    memcpy(buffer, first -> buffer, first -> length);
    memcpy(buffer + first -> length, second -> buffer, second -> length);

    String_ptr string = create_string(buffer);
    if (!string)
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }
    free(buffer);
    buffer = NULL;
    return string;
}