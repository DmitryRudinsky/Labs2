#include "options.h"

#include <limits.h>
#include <stdbool.h>

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

bool IsNumber(const char* str) {
    if (*str == '-' || *str == '+') {
        str++;
    }

    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

void PrintError(int error) {
    switch (error) {
        case OPT_INVALID_NUMBER:
            printf("\n\"Некорректное число\"\n");
            break;
        case OPT_UNKNOWN_OPTION:
            printf("\n\"Неизвестная опция\"\n");
            break;
        case OPT_INVALID_ARGUMENTS:
            printf("\nНеверные аргументы.\n");
            break;
        case OPT_SUCCESS:
            printf("\nУспешное выполнение.\n");
            break;
    }
}

bool IsPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

long long Factorial(int num) {
    if (num < 0) {
        printf("Факториал не определен для отрицательных чисел.\n");
        return -1;
    }
    if (num == 0 || num == 1) {
        return 1;
    }
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        if (result > LLONG_MAX / i) {
            printf("Переполнение при вычислении факториала %d!\n", num);
            return -1;
        }
        result *= i;
    }
    return result;
}

int SumNaturalNumbers(int x) {
    return x * (x + 1) / 2;
}

void PrintMultiples(int x) {
    if (x <= 0) {
        printf("Неверный ввод. x должен быть больше 0.\n");
        return;
    }
    printf("Натуральные числа, кратные %d до 100: ", x);
    for (int i = 1; i <= 100; i++) {
        if (i % x == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}


void SplitIntoHexDigits(int x) {
    if (x == 0) {
        printf("0\n");
        return;
    }
    if (x < 0) {
        printf("-");
        x = -x;
    }
    char hexDigits[20];
    int index = 0;
    while (x > 0) {
        int digit = x % 16;
        if (digit < 10) {
            hexDigits[index] = '0' + digit;
        } else {
            hexDigits[index] = 'A' + (digit - 10);
        }
        x /= 16;
        index++;
    }
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", hexDigits[i]);
    }
    printf("\n");
}

void PrintPowerTable(int x) {
    if (x > 10 || x < 0) {
        printf("x должен быть не больше 10 для этой операции.\n");
        return;
    }
    for (int i = 1; i <= 10; i++) {
        printf("%d^%d = %.0f\n", x, i, pow(x, i));
    }
}

int GetOpts(int argc, char** argv, Options *option, int *number) {
    if (argc < 3) {
        PrintError(OPT_INVALID_ARGUMENTS);
        return OPT_INVALID_ARGUMENTS;
    }

    bool numberFound = false, optionFound = false;

    for (int i = 1; i < argc; i++) {
        if (IsNumber(argv[i])) {
            if (!numberFound) {
                *number = MyAtoi(argv[i]);
                numberFound = true;
            } else {
                PrintError(OPT_INVALID_ARGUMENTS);
                return OPT_INVALID_ARGUMENTS;
            }
        } else {
            if (!optionFound) {
                if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "/h") == 0) {
                    *option = OPT_H;
                } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "/p") == 0) {
                    *option = OPT_P;
                } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "/s") == 0) {
                    *option = OPT_S;
                } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "/e") == 0) {
                    *option = OPT_E;
                } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "/a") == 0) {
                    *option = OPT_A;
                } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "/f") == 0) {
                    *option = OPT_F;
                } else {
                    PrintError(OPT_INVALID_ARGUMENTS);
                    return OPT_INVALID_ARGUMENTS;
                }
                optionFound = true;
            } else {
                PrintError(OPT_INVALID_ARGUMENTS);
                return OPT_INVALID_ARGUMENTS;
            }
        }
    }

    if (!numberFound || !optionFound) {
        PrintError(OPT_INVALID_ARGUMENTS);
        return OPT_INVALID_ARGUMENTS;
    }

    return 0;
}

void HandleOptH(int number) {
    PrintMultiples(number);
}

void HandleOptP(int number) {
    if(number < 1) {
        printf("%d - отрицательное число.\n", number);
        return;
    }
    else if(number == 1) {
        printf("%d - это не простое и не составное.\n", number);
        return;
    }
    if (IsPrime(number)) {
        printf("%d - простое число.\n", number);
    } else {
        printf("%d - не простое число.\n", number);
    }
}

void HandleOptS(int number) {
    SplitIntoHexDigits(number);
}

void HandleOptE(int number) {
    PrintPowerTable(number);
}

void HandleOptA(int number) {
    if (number < 0) {
        printf("Число должно быть натуральным\n");
        return;
    }
    int sum = SumNaturalNumbers(number);
    printf("Сумма натуральных чисел до %d равна %d.\n", number, sum);
}

void HandleOptF(int number) {
    long long fact = Factorial(number);
    if (fact != -1) {
        printf("Факториал %d = %lld\n", number, fact);
    }
}
