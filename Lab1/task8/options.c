#include "options.h"

int IsDigit(char temp) {
    return (temp >= '0' && temp <= '9');
}

int IsAlpha(char symbol) {
    if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z')) {
        return 1;
    }
    return 0;
}

void InputError() {
    printf("Please, use the format:\n");
    printf("./my_program input_file_name.txt output_file_name.txt\n");
}

int IsDelimiter(char symbol) {
    return (symbol == ' ' || symbol == '\n' || symbol == '\t');
}

long long GetDecimalNumber(char *number, int base, int flag) {
    long long result = 0;
    long long power = 1;
    int length = strlen(number);
    int temp;
    int end = (flag == 1) ? 1 : 0;

    for (int i = length - 1; i >= end; --i) {
        if (number[i] >= '0' && number[i] <= '9') {
            temp = number[i] - '0';
        } else {
            temp = tolower(number[i]) - 'a' + 10;
        }
        if (result > (LLONG_MAX - temp * power)) {
            fprintf(stderr, "Переполнение при вычислении десятичного числа для %s\n", number);
            return 0;
        }
        result += temp * power;
        if (power > (LLONG_MAX / base)) {
            fprintf(stderr, "Переполнение при вычислении степени для %s\n", number);
            return 0;
        }
        power *= base;
    }

    if (flag == 1) {
        result *= -1;
    }

    return result;
}

int GetMinBase(char *number, int flag) {
    int maximum = 0;
    int temp;
    int length = strlen(number);
    int i = (flag == 1) ? 1 : 0;

    for (; i < length; ++i) {
        if (number[i] >= '0' && number[i] <= '9') {
            temp = number[i] - '0';
        } else {
            temp = tolower(number[i]) - 'a' + 10; //a = 10, z = 35
        }

        if (temp > maximum) {
            maximum = temp;
        }
    }

    if (maximum < 0 || maximum > 35) {
        return -1;
    }

    return maximum + 1;
}

int CheckWord(char *word) {
    if (*word == '-') {
        word++;
    }

    while (*word != '\0') {
        if (!IsDigit(*word) && !IsAlpha(*word)) {
            return 0;
        }
        word++;
    }

    return 1;
}

void ProcessFile(FILE *input, FILE *output) {
    char words_string[MAX_WORD_LENGTH];
    size_t length = 0;
    int flag = 0;
    char temp;

    while ((temp = fgetc(input)) != EOF) {
        if (IsDelimiter(temp) && flag) {
            flag = 0;
        } else if (!IsDelimiter(temp)) {
            flag = 1;
            length = 0;
            do {
                if (length >= MAX_WORD_LENGTH - 1) {
                    fprintf(stderr, "Ошибка: превышена максимальная длина слова.\n");
                    break;
                }
                words_string[length++] = temp;
            } while ((temp = fgetc(input)) != EOF && !IsDelimiter(temp));

            words_string[length] = '\0';

            if (!CheckWord(words_string)) {
                continue;
            }
            int base = GetMinBase(words_string, (words_string[0] == '-') ? 1 : 0);
            long long decimal_number = GetDecimalNumber(words_string, base, (words_string[0] == '-') ? 1 : 0);

            if (base != 1 && decimal_number == 0) {
                fprintf(output, "Для числа %s с минимальной системой счисления %d происходит переполнение\n", words_string, base);
            } else {
                fprintf(output, "%s %d %lld\n", words_string, base, decimal_number);
            }
        }
    }
}
