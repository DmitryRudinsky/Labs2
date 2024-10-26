#include "options.h"

double polynomialCalculator(double point, int power, ...) {
    power++;
    double result = 0;
    va_list number;
    va_start(number, power);
    for (int i = 0; i < power; i++){
        result = result * point + va_arg(number, double);
    }
    va_end(number);
    return result;
}

int signFunc(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int convexPolygon(int amount, ...) {
    amount *= 2;
    va_list points;
    va_start(points, amount);
    if (amount < 6) {
        return too_few_arguments;
    }
    double x_first = va_arg(points, double);
    double y_first = va_arg(points, double);
    double x = x_first, y = y_first;
    double x_new = va_arg(points, double), y_new = va_arg(points, double);
    double new_x_vector = x_new - x;
    double new_y_vector = y_new - y;
    double x_vector, y_vector;
    for (int i = 0; i < amount/2 - 2; i++){
        x = x_new;
        y = y_new;
        x_vector = new_x_vector;
        y_vector = new_y_vector;
        x_new = va_arg(points, double);
        y_new = va_arg(points, double);
        new_x_vector = x_new - x;
        new_y_vector = y_new - y;
        if (x_vector * new_y_vector - y_vector * new_x_vector >= 0)
            return not_convex;
    }
    x_vector = new_x_vector;
    y_vector = new_y_vector;
    new_x_vector = x_first - x_new;
    new_y_vector = y_first - y_new;
    if (x_vector * new_y_vector - y_vector * new_x_vector >= 0)
        return not_convex;
    return convex;
}

bool isKaprekar(unsigned long long n, int base) {
    unsigned long long square = n * n;
    char* squareStr = (char*)malloc(50 * sizeof(char));
    if (squareStr == NULL) {
        perror("Ошибка выделения памяти");
        return false;
    }
    sprintf(squareStr, "%llu", square);
    int len = strlen(squareStr);
    bool result = false;
    for (int i = 1; i < len; ++i) {
        char* leftPart = (char*)malloc((i + 1) * sizeof(char));
        char* rightPart = (char*)malloc((len - i + 1) * sizeof(char));
        if (leftPart == NULL || rightPart == NULL) {
            perror("Ошибка выделения памяти");
            free(leftPart);
            free(rightPart);
            free(squareStr);
            return false;
        }
        strncpy(leftPart, squareStr, i);
        leftPart[i] = '\0';
        strcpy(rightPart, squareStr + i);
        unsigned long long leftNum = strtoull(leftPart, NULL, base);
        unsigned long long rightNum = strtoull(rightPart, NULL, base);
        if (rightNum != 0 && leftNum + rightNum == n) {
            result = true;
        }
        free(leftPart);
        free(rightPart);
    }
    free(squareStr);
    return result;
}

void findKaprekarNumbers(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        char* numStr = va_arg(args, char*);

        unsigned long long num = strtoull(numStr, NULL, base);

        if (isKaprekar(num, base)) {
            printf("Число %llu (основание %d) является числом Капрекара\n", num, base);
        } else {
            printf("Число %llu (основание %d) не является числом Капрекара\n", num, base);
        }
    }

    va_end(args);
}

