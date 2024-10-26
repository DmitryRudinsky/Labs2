#include "options.h"

int main() {
    ShowMenu(1);
    char *result = NULL;
    int tmp = GetString(&result);
    if (tmp == kNoMemory) {
        PrintError(tmp);
        free(result);
        result = NULL;
        return kNoMemory;
    }

    while (BaseValidCheck(result) == kIncorrectConsoleInput) {
        free(result);
        result = NULL;
        printf("\nBase should be a number between 2 and 36!\nTry again: ");
        tmp = GetString(&result);
        if (tmp == kNoMemory) {
            PrintError(tmp);
            free(result);
            result = NULL;
            return kNoMemory;
        }
    }

    int base = MyAtoi(result);
    free(result);
    result = NULL;

    ShowMenu(0);
    int i = 1;
    printf("%d. ", i);
    tmp = GetString(&result);
    if (tmp == kNoMemory) {
        PrintError(tmp);
        free(result);
        result = NULL;
        return kNoMemory;
    }

    long long maximum = 0;
    int curr_decimal;
    int res = strcmp(result, "Stop");

    while (res != 0) {
        while (NumberCheckValid(result, base) != kSuccess) {
            free(result);
            result = NULL;
            printf("Number should be in %d base. Try again.\n", base);
            printf("%d. ", i);
            tmp = GetString(&result);
            if (tmp == kNoMemory) {
                PrintError(tmp);
                free(result);
                result = NULL;
                return kNoMemory;
            }
            res = strcmp(result, "Stop");
            if (res == 0) {
                break;
            }
        }

        if (res == 0) {
            break;
        }

        curr_decimal = GetDecimalNumber(result, base);
        if (curr_decimal >= 0 && abs(curr_decimal) > llabs(maximum)) {
            maximum = curr_decimal;
        }

        i++;
        free(result);
        result = NULL;
        printf("%d. ", i);
        tmp = GetString(&result);
        if (tmp == kNoMemory) {
            PrintError(tmp);
            free(result);
            result = NULL;
            return kNoMemory;
        }
        res = strcmp(result, "Stop");
    }

    if (i == 1) {
        printf("\nNO NUMBERS WERE INPUTTED. FINISHING THE PROGRAM\n");
        return kIncorrectInput;
    }

    printf("Decimal maximum: %lld\n", maximum);

    int size = GetLength(maximum, base);
    char *based_maximum = NULL;
    res = ToBase(&based_maximum, size, maximum, base);

    if (res == kNoMemory) {
        free(based_maximum);
        based_maximum = NULL;
        PrintError(kNoMemory);
        return kNoMemory;
    } else {
        printf("Maximum in original base: %s\n", based_maximum);
    }

    free(based_maximum);

    int count_nine = 0;
    for (int i = 0; i < 4; ++i) {
        count_nine += 9;
        size = GetLength(maximum, count_nine);
        based_maximum = NULL;
        res = ToBase(&based_maximum, size, maximum, count_nine);
        if (res == kNoMemory) {
            PrintError(res);
        } else {
            printf("Maximum in %d base: %s\n", count_nine, based_maximum);
        }
        free(based_maximum);
    }

    printf("\n____________________________________\n");
    printf("\nThe program has finished.\n");
    printf("\n____________________________________\n");
    return 0;
}
