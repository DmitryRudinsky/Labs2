#ifndef STUDENT_H
#define STUDENT_H

#include "string.h"
#include <stdio.h>

typedef struct
{
    unsigned int id;
    String_ptr name;
    String_ptr surname;
    String_ptr group;
    unsigned char * grades;
    unsigned int grades_length;
} Student, *Student_ptr, **Student_array;

// creation
Student_ptr create_student(const int id, const char * name, const char * surname, const char * group, const unsigned char * grades, const int quantity);

// searching
int id_searching(const Student_array students, const int length, Student_array * result, const unsigned int id);
int surname_searching(const Student_array students, const int length, Student_array * result, const char * surname);
int name_searching(const Student_array students, const int length, Student_array * result, const char * name);
int group_searching(const Student_array students, const int length, Student_array * result, const char * group);

// comparators
int id_compare(const Student_ptr * first, const Student_ptr * second);
int surname_compare(const Student_ptr * first, const Student_ptr * second);
int name_compare(const Student_ptr * first, const Student_ptr * second);
int group_compare(const Student_ptr * first, const Student_ptr * second);

// sorting
void id_sort(Student_array students, const int length);
void surname_sort(Student_array students, const int length);
void name_sort(Student_array students, const int length);
void group_sort(Student_array students, const int length);

// printing
void print_students(FILE * file, Student_array students, int length);
void print_student_info(FILE * file, Student_ptr student);
void print_best_students(FILE * file, Student_array students, int length);

// deleting and appending
void delete_student(Student_ptr student);
void delete_students(Student_array students, const int length);
int append_student(const Student_ptr student, Student_array * students, int length);

// other
double get_full_average(Student_array students, int length);
double get_average(Student_ptr student);

#endif