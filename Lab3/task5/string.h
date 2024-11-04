#ifndef STRING_H
#define STRING_H

typedef struct
{
    char * buffer;
    int length;
} String, *String_ptr;

String_ptr create_string(const char * buffer);
void delete_string(String_ptr string);
int strings_order_relation(const String_ptr first, const String_ptr second);
int strings_cmp(const String_ptr first, const String_ptr second);
void strings_copy(const String_ptr from, String_ptr to);
String_ptr dublicate(const String_ptr string);
String_ptr concatenation(const String_ptr first, const String_ptr second);
int string_copy_dynamic(String_ptr new_string, const String_ptr string);

#endif