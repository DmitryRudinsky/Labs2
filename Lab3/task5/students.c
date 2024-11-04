#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "student.h"
#include <math.h>

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2
};

Student_ptr create_student(const int id, const char * name, const char * surname, const char * group, const unsigned char * grades, const int quantity)
{
    Student_ptr student = (Student_ptr)malloc(sizeof(Student));
    if (!student) return NULL;

    student -> id = id;
    student -> name = create_string(name);
    if (!(student -> name))
    {
        free(student);
        student = NULL;
        return NULL;
    }
    student -> surname = create_string(surname);
    if (!(student -> surname))
    {
        free(student -> name);
        student -> name = NULL;
        free(student);
        student = NULL;
        return NULL;
    }
    student -> group = create_string(group);
    if (!(student -> surname))
    {
        free(student -> name);
        student -> name = NULL;
        free(student -> surname);
        student -> surname = NULL;
        free(student);
        student = NULL;
        return NULL;
    }
    student -> grades = (unsigned char*)malloc(quantity * sizeof(unsigned char));
    if (!(student -> grades))
    {
        free(student -> group);
        student -> group = NULL;
        free(student -> name);
        student -> name = NULL;
        free(student -> surname);
        student -> surname = NULL;
        free(student);
        student = NULL;
        return NULL;
    }
    memcpy(student -> grades, grades, quantity);
    student -> grades_length = quantity;
    return student;
}

// возвращает количество найденных студентов, а в резалт их сохраняет
int id_searching(const Student_array students, const int length, Student_array * result, const unsigned int id)
{
    int len = 0;
    for (int i = 0; i < length; ++i)
    {
        if (students[i] -> id == id)
        {
            len = append_student(students[i], result, len);
            if (len == no_memory)
            {
                delete_students(students, length);
                return no_memory;
            }
        }
    }
    return len;
}

int surname_searching(const Student_array students, const int length, Student_array * result, const char * surname)
{
    int len = 0;
    for (int i = 0; i < length; ++i)
    {
        if (strcmp(students[i] -> surname -> buffer, surname) == success)
        {
            len = append_student(students[i], result, len);
            if (len == no_memory)
            {
                delete_students(students, length);
                return no_memory;
            }
        }
    }
    return len;
}

int name_searching(const Student_array students, const int length, Student_array * result, const char * name)
{
    int len = 0;
    for (int i = 0; i < length; ++i)
    {
        if (strcmp(students[i] -> name -> buffer, name) == success)
        {
            len = append_student(students[i], result, len);
            if (len == no_memory)
            {
                delete_students(students, length);
                return no_memory;
            }
        }
    }
    return len;
}

int group_searching(const Student_array students, const int length, Student_array * result, const char * group)
{
    int len = 0;
    for (int i = 0; i < length; ++i)
    {
        if (strcmp(students[i] -> group -> buffer, group) == success)
        {
            len = append_student(students[i], result, len);
            if (len == no_memory)
            {
                delete_students(students, length);
                return no_memory;
            }
        }
    }
    return len;
}

void id_sort(Student_array students, const int length)
{
    qsort(students, length, sizeof(Student_ptr), (int (*) (const void *, const void *)) id_compare);
}

int id_compare(const Student_ptr * first, const Student_ptr * second)
{
    if ((*first) -> id > (*second) -> id) return 1;
    if ((*first) -> id < (*second) -> id) return -1;
    return 0;
}

void surname_sort(Student_array students, const int length)
{
    qsort(students, length, sizeof(Student_ptr), (int (*) (const void *, const void *)) surname_compare);
}

int surname_compare(const Student_ptr * first, const Student_ptr * second)
{
    return strcmp((*first) -> surname -> buffer, (*second) -> surname -> buffer);
}

void name_sort(Student_array students, const int length)
{
    qsort(students, length, sizeof(Student_ptr), (int (*) (const void *, const void *)) name_compare);
}

int name_compare(const Student_ptr * first, const Student_ptr * second)
{
    return strcmp((*first) -> name -> buffer, (*second) -> name -> buffer);
}

void group_sort(Student_array students, const int length)
{
    qsort(students, length, sizeof(Student_ptr), (int (*) (const void *, const void *)) group_compare);
}

int group_compare(const Student_ptr * first, const Student_ptr * second)
{
    return strcmp((*first) -> group -> buffer, (*second) -> group -> buffer);
}

void print_students(FILE * file, Student_array students, int length)
{
    if (length == 0)
    {
        fprintf(file, "NO STUDENTS\n");
        return;
    }
    for (int i = 0; i < length; ++i)
    {
        fprintf(file, "%d)\n", i + 1);
        print_student_info(file, students[i]);
        fprintf(file, "\n");
    }
}

void print_student_info(FILE * file, Student_ptr student)
{
    double average = get_average(student);
    fprintf(file, "Name: %s\n", student -> name -> buffer);
    fprintf(file, "Surname: %s\n", student -> surname -> buffer);
    fprintf(file, "Group: %s\n", student -> group -> buffer);
    fprintf(file, "Average grade: %.2f\n", average);
}

void print_best_students(FILE * file, Student_array students, int length)
{
    double eps = 0.000000000000000001;
    double average, full_average;
    full_average = get_full_average(students, length);
    fprintf(file, "\nBest students whos average grade is more than %.2f:\n", full_average);
    for (int i = 0; i < length; ++i)
    {
        average = get_average(students[i]);
        if (average - full_average > eps)
        {
            fprintf(file, "%s %s - %.2f\n", students[i] -> name -> buffer, students[i] -> surname -> buffer, average);
        }
    }
}

double get_full_average(Student_array students, int length)
{
    int res = 0;
    int quantity;
    int count = 0;
    for (int i = 0; i < length; ++i)
    {
        quantity = students[i] -> grades_length;
        count += quantity;
        for (int j = 0; j < quantity; ++j)
        {
            res += (students[i] -> grades)[j];
        }
    }
    return res / ((double) count);
}

// средняя оценка, длина массива оценок
double get_average(Student_ptr student)
{
    int res = 0;
    int length = student -> grades_length;
    for (int i = 0; i < length; ++i)
    {
        res += (student -> grades)[i];
    }
    return res / ((double) length);
}

int append_student(const Student_ptr student, Student_array * students, int length)
{
    length++;
    Student_array temp;
    temp = (Student_array)realloc(*students, length * sizeof(Student_ptr));
    if (!temp)
    {
        if (!(*students)) return no_memory;
        // без специальной функции, чтобы не удалить полностью студентов из памяти
        free(*students);
        *students = NULL;
        return no_memory;
    }
    *students = temp;
    (*students)[length - 1] = student;
    return length;
}

void delete_students(Student_array students, const int length)
{
    if (length == 0) return;
    for (int i = 0; i < length; ++i)
    {
        delete_student(students[i]);
    }
    free(students);
    students = NULL;
}

void delete_student(Student_ptr student)
{
    delete_string(student -> name);
    delete_string(student -> surname);
    delete_string(student -> group);
    free(student);
    student = NULL;
}