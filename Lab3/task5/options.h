#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string.h"
#include "student.h"


#ifndef LAB3_OPTIONS_H
#define LAB3_OPTIONS_H

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2,
    incorrect_input = -3,
    file_open_error = -4
};

void print_error(int error);

int get_students_from_file(FILE * file, Student_array * students);
int letters_only(char * string);
int digits_only(char * string);
void menu();
int get_command();
void switch_commands(FILE * file, Student_array students, int length, int command);
void id_search(FILE * file, Student_array students, int length);
void surname_search(FILE * file, Student_array students, int length);
void name_search(FILE * file, Student_array students, int length);
void group_search(FILE * file, Student_array students, int length);

#endif //LAB3_OPTIONS_H
