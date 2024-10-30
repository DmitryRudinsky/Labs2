#include "options.h"

int main(int argc, char *argv[]) {
    int result = CheckValidation(argc, argv);

    switch (result) {
        case TOO_MANY_OR_TOO_FEW_ARGUMENTS:
            printf("Incorrect input! Too many or too few arguments"
                   "\nPlease, use the right format:"
                   "\n-flag 'file.txt'"
                   "\n      or"
                   "\n-'n'flag 'file.txt' 'out_file.txt'"
                   "\n");
            return 0;

        case INCORRECT_FLAG:
            printf("Incorrect flag input!"
                   "\nPlease, use the right format:"
                   "\n-flag 'file.txt'"
                   "\n      or"
                   "\n-'n'flag 'file.txt' 'out_file.txt'"
                   "\n");
            return 0;

        case INCORRECT_FILE_INPUT:
            printf("Incorrect file input!"
                   "\nPlease, use the right format:"
                   "\n-flag 'file.txt'"
                   "\n      or"
                   "\n-'n'flag 'file.txt' 'out_file.txt'"
                   "\n");
            return 0;

        case INCORRECT_OUTPUT_FILE_INPUT:
            printf("Incorrect output-file input!"
                   "\nPlease, use the right format:"
                   "\n-flag 'file.txt'"
                   "\n      or"
                   "\n-'n'flag 'file.txt' 'out_file.txt'"
                   "\n");
            return 0;

        case VALIDATION_SUCCESS:
            printf("Validation passed!\n");
            break;

        default:
            printf("Unknown error occurred!\n");
            return 0;
    }

    char *input_file = argv[2];
    char state;
    char output_file[N] = {'\0'};
    int length;

    if (argc == 3) {
        const char* temp = "out_";
        length = strlen(input_file);
        int temp_length = strlen(temp);
        int new_length = length + temp_length;

        GenerateName(output_file, input_file, new_length, length);
        state = argv[1][1];
    } else {
        length = strlen(argv[3]);
        strncpy(output_file, argv[3], length);
        output_file[length] = '\0';
        state = argv[1][2];
    }

    FILE *input = fopen(input_file, "task4");
    if (!input) {
        printf("ERROR: input-file can not be opened.\n");
        return 0;
    }

    FILE *output = fopen(output_file, "w");
    if (!output) {
        printf("ERROR: output-file can not be opened.\n");
        fclose(input);
        return 0;
    }

    switch (state) {
        case 'd':
            result = FlagD(input, output);
            break;

        case 'i':
            result = FlagI(input, output);
            break;

        case 's':
            result = FlagS(input, output);
            break;

        case 'a':
            result = FlagA(input, output);
            break;

        default:
            printf("Unknown flag.\n");
            fclose(input);
            fclose(output);
            return 0;
    }

    if (!result) {
        printf("File Error\n");
    }

    fclose(input);
    fclose(output);
    printf("The program was finished. Check the file.\n");
    return 0;
}
