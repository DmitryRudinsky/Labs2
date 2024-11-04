#include "options.h"

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        print_error(incorrect_input);
        printf("Do not forget to include input and output files!\n");
        return incorrect_input;
    }

    FILE * input = fopen(argv[1], "r");
    if (!input)
    {
        print_error(file_open_error);
        return file_open_error;
    }
    FILE * output = fopen(argv[2], "w");
    if (!output)
    {
        fclose(input);
        print_error(file_open_error);
        return file_open_error;
    }

    Student_array students = NULL;
    int length = get_students_from_file(input, &students);
    if (length < 0)
    {
        print_error(length);
        return length;
    }

    int command = -1;
    while (command != success)
    {
        menu();
        command = get_command();
        if (command == success) break;
        switch_commands(output, students, length, command);
    }

    delete_students(students, length);
    printf("Program has finished correctly.");
    fclose(input);
    fclose(output);
    return success;
}
