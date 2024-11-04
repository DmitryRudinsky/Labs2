#include "options.h"

int main(int argc, char * argv[])
{
    if (argc != 4)
    {
        print_error(incorrect_input);
        return incorrect_input;
    }
    char * input_name = argv[1];
    char * output_name = argv[3];
    char * flag = argv[2];
    if (!(flag[0] == '-' || flag[0] == '/') || !(flag[1] == 'a' || flag[1] == 'd'))
    {
        print_error(incorrect_input);
        return incorrect_input;
    }

    FILE * input = fopen(input_name, "r");
    if (!input)
    {
        print_error(file_open_error);
        return file_open_error;
    }

    FILE * output = fopen(output_name, "w");
    if (!output)
    {
        fclose(input);
        print_error(file_open_error);
        return file_open_error;
    }

    int length = 1;
    Employee_array employers = (Employee_array) malloc(length * sizeof(Employee_ptr));
    if (!employers)
    {
        fclose(input);
        fclose(output);
        return no_memory;
    }
    int result = get_employers(input, &employers, length);
    if (result < 0)
    {
        print_error(result);
        fclose(input);
        fclose(output);
        return result;
    }
    length = result;
    print_employers(employers, output, length, flag[1]);

    fclose(input);
    fclose(output);

    delete_employers(employers, length);

    printf("The program has finished correctly.\n");
    return success;
}