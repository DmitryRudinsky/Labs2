#include "options.h"

int MyAtoi(char *str) {
    while (*str == '\n' || *str == ' ' || *str == '\r') {
        str++;
    }

    bool negative = false;
    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    int result = 0;

    while (*str >= '0' && *str <= '9') {
        if (result > (INT_MAX - (*str - '0')) / 10) {
            return negative ? INT_MIN : INT_MAX;
        }
        result = (result * 10) + (*str - '0');
        str++;
    }

    if (*str == '.') {
        return 0;
    }

    return negative ? -result : result;
}

int GetLength(int number, int base) {
    int result = 0;
    int flag = 0;

    if (number < 0) {
        flag = 1;
        number *= -1;
    }

    while (number > 0) {
        result++;
        number /= base;
    }

    if (flag == 1) {
        result += 1;
    }

    return result;
}

int ToBase(char **buf, int size, int number, int base) {
    *buf = malloc(size * sizeof(char));
    if (*buf == NULL) return kNoMemory;

    char *ptr = *buf + size;
    *(ptr--) = '\0';
    int flag = 0;

    if (number < 0) {
        flag = 1;
    }

    int remainder;
    number = abs(number);
    while (number > 0) {
        remainder = number % base;
        *(ptr--) = (remainder > 9) ? remainder - 10 + 'A' : remainder + '0';
        number /= base;
    }
    if (flag == 1) *(ptr) = '-';
    return kSuccess;
}

int GetDecimalNumber(char *number, int base) {
    int result = 0;
    char *ptr = number - 1;
    int flag = 0;

    if (*(++ptr) == '-') {
        flag = 1;
    }
    else {
        --ptr;
    }

    while (*(++ptr)) {
        result = result * base + (isdigit(*ptr) ? *ptr - '0' : *ptr - 'A' + 10);
    }

    if (flag == 1) result *= -1;

    return result;
}

int NumberCheckValid(char *number, int base) {
    int length = strlen(number);
    int temp;
    int i = 0;

    if (number[0] == '-') i = 1;

    for (i; i < length; ++i) {
        if (isalpha(number[i])) {
            temp = tolower(number[i]) - 'a' + 10;
            if (temp >= base) {
                return kIncorrectInput;
            }
        } else if (isdigit(number[i])) {
            temp = number[i] - '0';
            if (temp >= base) {
                return kIncorrectInput;
            }
        } else {
            return kIncorrectInput;
        }
    }

    return kSuccess;
}

int BaseValidCheck(char *base) {
    if (IsDigit(base) == 0) {
        return kIncorrectConsoleInput;
    }

    int base_int = MyAtoi(base);
    if (!(base_int > 1 && base_int < 37)) {
        return kIncorrectConsoleInput;
    }

    return kSuccess;
}

void ShowMenu(int state) {
    switch (state) {
        case 1:
            printf("\n____________________________________\n");
            printf("\t\tMENU\n");
            printf("\n____________________________________\n");
            printf("Please, write down the base (from 2 to 36): ");
            break;
        case 2:
            printf("Write down numbers in this base. To stop write down 'Stop'.\n");
            break;
    }
}

void PrintError(int error) {
    switch (error) {
        case kIncorrectInput:
            printf("\nIncorrect input! Please, use the format:\n");
            printf(".\a.exe A B\n");
            printf("A and B should be more than -2 147 483 648 and less than 2 147 483 647\n");
            printf("A > B\n");
            break;
        case kIncorrectConsoleInput:
            printf("\nIncorrect input! Please, input number that is more than -2 147 483 648 and less than 2 147 483 647\n");
            break;
        case kOneElementArray:
            printf("\nMinimum and maximum cannot be changed, because array has only one element\n");
            break;
        case kNoMemory:
            printf("\nComputer doesn't have enough memory for this calculation\n");
            break;
    }
}

int IsDigit(char *number) {
    if (number == "-") {
        return 0;
    }
    if (*number == '-') {
        number++;
    }

    while (*number != '\0') {
        if (!(*number >= '0' && *number <= '9')) {
            return 0;
        }
        number++;
    }
    return 1;
}

int GetString(char **new_string) {
    int length = 2;
    char *string = malloc(length * sizeof(char));
    if (string == NULL) {
        return kNoMemory;
    }

    char temp;
    char *temp_string;
    temp = getc(stdin);
    int count = 0;

    while (temp != '\n') {
        if (length <= count) {
            length *= 2;
            temp_string = (char *)realloc(string, length * sizeof(char));
            if (temp_string == NULL) {
                free(string);
                return kNoMemory;
            }
            string = temp_string;
        }
        string[count] = temp;
        count++;
        temp = getc(stdin);
    }
    string[count] = '\0';
    *new_string = string;
    return kSuccess;
}