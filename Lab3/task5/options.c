#include "options.h"

void menu()
{
    printf("\nCommands menu\n\n");
    printf("1. Find student through id.\n");
    printf("2. Find all students through surname.\n");
    printf("3. Find all students through name.\n");
    printf("4. Find all students in group.\n");
    printf("5. Sort students with id.\n");
    printf("6. Sort students with surname.\n");
    printf("7. Sort students with name.\n");
    printf("8. Sort students with group.\n");
    printf("9. Print best students.\n");
    printf("0. Exit.\n");
}

int get_command()
{
    int result, res;
    res = -1;
    while (res <= 0)
    {
        printf("\nInput form: ");
        res = scanf("%d", &result);
        fflush(stdin);
    }
    return result;
}

void switch_commands(FILE * file, Student_array students, int length, int command)
{
    switch (command)
    {
        case 1:
            id_search(file, students, length);
            break;
        case 2:
            surname_search(file, students, length);
            break;
        case 3:
            name_search(file, students, length);
            break;
        case 4:
            group_search(file, students, length);
            break;
        case 5:
            id_sort(students, length);
            fprintf(file, "\nResult of id sorting:\n");
            print_students(file, students, length);
            printf("\nResult of id sorting:\n");
            print_students(stdout, students, length);
            break;
        case 6:
            surname_sort(students, length);
            fprintf(file, "\nResult of surname sorting:\n");
            print_students(file, students, length);
            fprintf(stdout, "\nResult of surname sorting:\n");
            print_students(stdout, students, length);
            break;
        case 7:
            name_sort(students, length);
            fprintf(file, "\nResult of name sorting:\n");
            print_students(file, students, length);
            fprintf(stdout, "\nResult of name sorting:\n");
            print_students(stdout, students, length);
            break;
        case 8:
            group_sort(students, length);
            fprintf(file, "\nResult of group sorting:\n");
            print_students(file, students, length);
            fprintf(stdout, "\nResult of group sorting:\n");
            print_students(stdout, students, length);
            break;
        case 9:
            print_best_students(file, students, length);
            print_best_students(stdout, students, length);
            break;
        default: break;
    }
}

void id_search(FILE * file, Student_array students, int length)
{
    Student_array temp = NULL;
    int id;
    printf("\nInput student's id: ");
    while (scanf("%d", &id) < 0)
    {
        printf("\nTry again: ");
    }
    printf("\n");
    int result = id_searching(students, length, &temp, id);
    fprintf(file, "Students with id %d:\n", id);
    print_students(file, temp, result);
    fprintf(stdout, "Students with id %d:\n", id);
    print_students(stdout, temp, result);
    if (result != 0)
    {
        free(temp);
        temp = NULL;
    }
}

void surname_search(FILE * file, Student_array students, int length)
{
    Student_array temp = NULL;
    char surname[30];
    printf("\nInput student's surname: ");
    while (scanf("%s", surname) < 0)
    {
        printf("\nTry again: ");
    }
    printf("\n");
    int result = surname_searching(students, length, &temp, surname);
    fprintf(file, "Students with surname %s:\n", surname);
    print_students(file, temp, result);
    fprintf(stdout, "Students with surname %s:\n", surname);
    print_students(stdout, temp, result);
    if (result != 0)
    {
        free(temp);
        temp = NULL;
    }
}

void name_search(FILE * file, Student_array students, int length)
{
    Student_array temp = NULL;
    char name[30];
    printf("\nInput student's name: ");
    while (scanf("%s", name) < 0)
    {
        printf("\nTry again: ");
    }
    printf("\n");
    int result = name_searching(students, length, &temp, name);
    fprintf(file, "Students with name %s:\n", name);
    print_students(file, temp, result);
    fprintf(stdout, "Students with name %s:\n", name);
    print_students(stdout, temp, result);
    if (result != 0)
    {
        free(temp);
        temp = NULL;
    }
}

void group_search(FILE * file, Student_array students, int length)
{
    Student_array temp = NULL;
    char group[30];
    printf("\nInput student's group: ");
    while (scanf("%s", group) < 0)
    {
        printf("\nTry again: ");
    }
    printf("\n");
    int result = group_searching(students, length, &temp, group);
    fprintf(file, "Students with group %s:\n", group);
    print_students(file, temp, result);
    fprintf(stdout, "Students with group %s:\n", group);
    print_students(stdout, temp, result);
    if (result != 0)
    {
        free(temp);
        temp = NULL;
    }
}

int get_students_from_file(FILE * file, Student_array * students)
{
    int len = 30;
    int id;
    char name[len], surname[len], group[len];
    int grade_int;
    int quantity = 0;
    unsigned char * grades = (unsigned char*)malloc(quantity * sizeof(unsigned char));
    unsigned char * temp;
    int result;

    Student_array temp1 = NULL;

    int length = 0;
    char symbol;

    Student_ptr student;

    while (!feof(file))
    {
        result = fscanf(file, "%d %s %s %s", &id, name, surname, group);
        if (result != 4)
        {
            delete_students(*students, length);
            return incorrect_input;
        }

        quantity = id_searching(*students, length, &temp1, id);
        if (quantity != success)
        {
            free(temp1);
            temp1 = NULL;
            delete_students(*students, length);
            return incorrect_input;
        }
        free(temp1);
        temp1 = NULL;
        if (letters_only(name) != success)
        {
            delete_students(*students, length);
            return incorrect_input;
        }
        if (letters_only(surname) != success)
        {
            delete_students(*students, length);
            return incorrect_input;
        }
        if (digits_only(group) != success)
        {
            delete_students(*students, length);
            return incorrect_input;
        }

        while (!feof(file))
        {
            fscanf(file, "%d", &grade_int);
            if (grade_int < 2 || grade_int > 5)
            {
                delete_students(*students, length);
                return incorrect_input;
            }

            quantity++;
            temp = (unsigned char*) realloc(grades, quantity * sizeof(unsigned char));
            if (!temp)
            {
                free(grades);
                grades = NULL;
                delete_students(*students, length);
                return no_memory;
            }
            grades = temp;
            grades[quantity - 1] = grade_int;

            symbol = fgetc(file);
            if (symbol == '\n') break;
        }
        student = create_student(id, name, surname, group, grades, quantity);

        free(grades);
        grades = NULL;
        quantity = 0;
        length = append_student(student, students, length);
    }
    return length;
}

int letters_only(char * string)
{
    int length = strlen(string);

    for (int i = 0; i < length; ++i)
    {
        if (!isalpha(string[i])) return fail;
    }
    return success;
}

int digits_only(char * string)
{
    int length = strlen(string);

    for (int i = 0; i < length; ++i)
    {
        if (!isdigit(string[i])) return fail;
    }
    return success;
}

void print_error(int error)
{
    switch(error)
    {
        case no_memory:
            printf("\nComputer doesnot have enough memory for this calculation.");
            break;
        case incorrect_input:
            printf("\nIncorrect input.\n");
            break;
        case file_open_error:
            printf("\nCannot open file!\n");
            break;
    }
}