#include "options.h"

int InFlags(char item) {
    char flags[] = {'d', 'i', 's', 'a'};
    int length = strlen(flags);

    for (int i = 0; i < length; ++i) {
        if (item == flags[i]) return 1;
    }
    return 0;
}

int CheckValidation(int length, char *arguments[]) {
    if (length < 3 || length > 4) {
        return TOO_MANY_OR_TOO_FEW_ARGUMENTS;
    }

    if (length == 3) {
        char *flag = arguments[1];
        if (!(flag[0] == '-' || flag[0] == '/')) {
            return INCORRECT_FLAG;
        }
        int result = InFlags(flag[1]);
        if (!result) {
            return INCORRECT_FLAG;
        }
        return VALIDATION_SUCCESS;
    }

    if (length == 4) {
        char *flag = arguments[1];
        if (!((flag[0] == '-' || flag[0] == '/') && flag[1] == 'n')) {
            return INCORRECT_FLAG;
        }
        int result = InFlags(flag[2]);
        if (!result) {
            return INCORRECT_FLAG;
        }
        if (!strcmp(arguments[2], arguments[3])) {
            return INCORRECT_OUTPUT_FILE_INPUT;
        }
        return VALIDATION_SUCCESS;
    }

    return INCORRECT_FLAG; // добавлен случай по умолчанию
}

void GenerateName(char new_name[], const char* name, int new_length, int length) {
    const char* temp = "out_";
    int temp_length = strlen(temp);
    int count = -1;

    for (int i = length - 1; i >= 0; --i) {
        if (name[i] == '/') {
            count = i;
            break;
        }
    }

    for (int i = 0; i <= count; ++i) {
        new_name[i] = name[i];
    }

    for (int i = count + 1, j = 0; i < count + 1 + temp_length && j < temp_length; ++i, ++j) {
        new_name[i] = temp[j];
    }

    for (int i = count + 1 + temp_length, j = count + 1; i < new_length && j < length; ++i, ++j) {
        new_name[i] = name[j];
    }

    new_name[new_length] = '\0';
}

int IsLetter(char temp) {
    return (temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z');
}

int IsDigit(char temp) {
    return (temp >= '0' && temp <= '9');
}

int FlagD(FILE* input, FILE* output) {
    char temp;
    while (!feof(input)) {
        if (ferror(input)) {
            return 0;
        }
        temp = fgetc(input);
        if (!(IsDigit(temp)) && temp != EOF) {
            if (ferror(output)) {
                return 0;
            }
            fputc(temp, output);
        }
    }
    return 1;
}

int FlagI(FILE* input, FILE* output) {
    char temp;
    char temp_2[20];
    int count = 0;

    while (!feof(input)) {
        if (ferror(input)) {
            return 0;
        }

        temp = fgetc(input);

        if (temp == '\n') {
            if (ferror(output)) {
                return 0;
            }
            fprintf(output, "Number of letters on this string: %d\n", count);
            fputs(temp_2, output);
            fputc('\n', output);
            count = 0;
        } else if (IsLetter(temp)) {
            count++;
        }
    }
    if (count > 0) {
        fputs("Number of letters on this string: ", output);
        sprintf(temp_2, "%d", count);
        fputs(temp_2, output);
        fputc('\n', output);
    }

    return 1;
}

int FlagS(FILE* input, FILE* output) {
    int count = 0;
    char temp;
    char temp_2[20];

    while (!feof(input)) {
        if (ferror(input)) {
            return 0;
        }
        temp = fgetc(input);

        if (temp == '\n') {
            if (ferror(output)) {
                return 0;
            }
            fprintf(output, "Number of non-letters, non-digits and non-space symbols on this string:  %d\n", count);
            fputs(temp_2, output);
            fputc('\n', output);
            count = 0;
        } else if (temp != ' ' && !IsDigit(temp) && !IsLetter(temp)) {
            count++;
        }
    }

    if (count > 0) {
        fputs("Number of non-letters, non-digits and non-space symbols on this string: ", output);
        sprintf(temp_2, "%d", count);
        fputs(temp_2, output);
        fputc('\n', output);
    }

    return 1;
}

int FlagA(FILE* input, FILE* output) {
    char temp;
    while (!feof(input)) {
        if (ferror(input)) {
            return 0;
        }

        temp = fgetc(input);

        if (ferror(output)) {
            return 0;
        }

        if ((IsDigit(temp) || temp == '\n') && temp != EOF) {
            fputc(temp, output);
        } else if (temp != EOF) {
            fprintf(output, "%X", temp);
        }
    }
    return 1;
}
