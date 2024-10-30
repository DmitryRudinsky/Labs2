#ifndef TASK1_OPTIONS_H
#define TASK1_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <limits.h>

typedef enum
{
    OK,
    INVALID_INPUT,
    INVALID_PARAMS,
    INVALID_ID,
    WEIRD_VALUES,
    OVERFLOW,
    MALLOC_ERROR,
    FILE_OPENING_ERROR,
    FILE_READING_ERROR,
    FILE_WRITING_ERROR,
    FILE_INVALID_DATA,
    UNKNOWN_ERROR
}status_code;

typedef enum
{
    help,
    add_mail_cmd,
    delete_mail_cmd,
    search_mail_cmd,
    deliver_cmd,
    all_mails_cmd,
    delivered_cmd,
    expired_cmd,
    exit_cmd,
    end
}commands_codes;

static const char* errors[] =
        {
                "Success\n",
                "Invalid input\n",
                "Invalid parameters were passed to the function\n",
                "Unavailable data access\n",
                "The problem is unsolvable for the given arguments\n",
                "Overflow error\n",
                "Memory allocation error\n",
                "Cannot open the file\n",
                "Errors occurred while reading the file\n",
                "Errors occurred while writing to the file\n",
                "The contents of the file contradict the condition of the task\n",
                "Unknown error\n"
        };


static const char* commands[] =
        {
                "help",
                "add mail",
                "delete mail",
                "search mail",
                "deliver",
                "all mails",
                "delivered",
                "expired",
                "exit",
                "undefined cmd"
        };


typedef struct String
{
    char* head;
    int length;
} String;

typedef struct Address
{
    String city;
    String street;
    int house_number;
    String building;
    int apartment_number;
    String receiver_id;
}Address;

typedef struct Mail
{
    Address receiver_address;
    double weight;
    String mail_id;
    String creation_time;
    String delivery_time;
    int is_delivered;
}Mail;

typedef struct
{
    Address office_addr;
    int mails_cnt;
    Mail* mails;
} Post;

status_code create_string(String* str, char* s);
status_code string_insert(String* str, char c);
status_code destruct_string(String* str);
int compare_strings(const String str1, const String str2);
int equal_strings(String left, String right);
status_code copy_string(const String source, String* dest);
status_code new_copy_string(const String source, String** dest);
status_code concat_string(String* first, const String second);
void print_string(const String str);
status_code destruct_address(Address* addr);
status_code destruct_mail(Mail* mail);
status_code destruct_post(Post* post);
int mail_comparator(const void* l, const void* r);
int mail_time_comparator(const void* l, const void* r);
status_code search_mail(const Post post, const String mail_ID, int* ind);
status_code add_mail_to_post(Post* post, const Mail mail);
status_code delete_mail_from_post(Post* post, const String mail_ID);
commands_codes identify_command(const String input);
status_code get_string(String* input);
status_code string_to_uint(const String str, int* n);
status_code string_to_udouble(const String str, double* n);
status_code get_time_string(String* str_time);
status_code check_uint_format(const String str, const int digits);
status_code check_time_format(const String str_time);
status_code get_id_string(String* id, int len);
status_code read_adress(Address* address);
status_code read_mail(Mail* mail);
status_code read_post(Post* post);
void print_mail_info(const Mail mail);
status_code compare_time_with_cur(const String str_time, int* has_come);
status_code print_mail_tab(Mail* mails, int cnt);
status_code search_some_mails(Post post, int delivered, Mail** ans, int* ans_len);


#endif //TASK1_OPTIONS_H
