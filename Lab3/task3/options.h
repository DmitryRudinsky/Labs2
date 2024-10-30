#ifndef TASK1_OPTIONS_H
#define TASK1_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    unsigned int id;
    char * name;
    char * surname;
    double salary;

} Employee, *Employee_ptr, **Employee_array;

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2,
    incorrect_input = -3,
    file_open_error = -4
};

void print_error(int error);

void print_employers(Employee_array employers, FILE * file, int length, char flag);
void delete_employers(Employee_array employers, int length);
int compare_increase(const Employee_ptr * first, const Employee_ptr * second);
int compare_decrease(const Employee_ptr * first, const Employee_ptr * second);
int get_employers(FILE * file, Employee_array * employers, int length);
void print_employee_info(Employee_ptr employee, FILE * file);
void delete_employee(Employee_ptr employee);
Employee_ptr create_employee(int id, const char * name, const char * surname, double salary);

#endif //TASK1_OPTIONS_H
