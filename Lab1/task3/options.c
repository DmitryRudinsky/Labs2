#include "options.h"

int FlagValidation(char *flag) {
    if (flag[2] != 0) {
        return 0;
    }
    if (flag[0] != '-' && flag[0] != '/') {
        return 0;
    }
    if (flag[1] != 'q' && flag[1] != 'm' && flag[1] != 't') {
        return 0;
    }
    return 1;
}

int ArgumentsAmountValidation(char flag, int argc) {
    if (flag == 'q' && argc != 6) {
        return 0;
    }
    if (flag == 'm' && argc != 4) {
        return 0;
    }
    if (flag == 't' && argc != 6) {
        return 0;
    }
    return 1;
}

int RealNumberValidation(char *number) {
    int i = 1;
    char symbol = number[0];
    int dot_counter = 0;
    if (symbol != '-' && (symbol < '0' || symbol > '9')) {
        return 0;
    }
    while (number[i] != 0) {
        symbol = number[i];
        if (symbol == '.') {
            dot_counter++;
            if (dot_counter == 2) {
                return 0;
            }
        }
        if (symbol != '.' && (symbol < '0' || symbol > '9')) {
            return 0;
        }
        i++;
    }
    return 1;
}

int IntegerNumberValidation(char *number) {
    int i = 1;
    char symbol = number[0];
    if (symbol != '-' && (symbol < '0' || symbol > '9')) {
        return 0;
    }
    while (number[i] != 0) {
        symbol = number[i];
        if (symbol < '0' || symbol > '9') {
            return 0;
        }
        i++;
    }
    if (MyAtoi(number) < 1) {
        return 0;
    }
    return 1;
}

int Triangle(double a, double b, double c, double epsilon) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Ошибка: стороны должны быть положительными числами.\n");
        return 0;
    }
    a = a * a;
    b = b * b;
    c = c * c;
    if (a < b) {
        if (b < c) {
            if (fabs(a + b - c) < epsilon) {
                return 1;
            }
        } else if (fabs(a + c - b) < epsilon) {
            return 1;
        }
    } else if (a < c) {
        if (fabs(a + b - c) < epsilon) {
            return 1;
        }
    } else if (fabs(b + c - a) < epsilon) {
        return 1;
    }
    return 0;
}

void Swap(double *coefficients, int i, int j) {
    double elem = coefficients[i];
    coefficients[i] = coefficients[j];
    coefficients[j] = elem;
}

int Permutations(double *coefficients, int amount, double epsilon) {
    int j = amount - 2;
    while (j != -1 && coefficients[j] - coefficients[j + 1] >= -epsilon) {
        j--;
    }
    if (j == -1) {
        return 0;
    }
    int i = amount - 1;
    while (coefficients[j] - coefficients[i] >= -epsilon) {
        i--;
    }
    Swap(coefficients, j, i);
    int k = j + 1, l = amount - 1;
    while (k < l) {
        Swap(coefficients, k++, l--);
    }
    return 1;
}

int EquationsRoots(double *roots, double *coefficients, double epsilon) {
    double a = coefficients[0];
    double b = coefficients[1];
    double c = coefficients[2];
    if (a <= epsilon) {
        if (b <= epsilon) {
            return -1;
        }
        roots[0] = -c / b;
        return 1;
    }
    double discriminant = b * b - 4 * a * c;
    if (discriminant > epsilon) {
        roots[0] = (-b + sqrt(discriminant)) / (2 * a);
        roots[1] = (-b - sqrt(discriminant)) / (2 * a);
        return 2;
    }
    if (fabs(discriminant) < epsilon) {
        roots[0] = -b / (2 * a);
        return 1;
    }
    return 0;
}

int Comp(const double *num1, const double *num2) {
    double eps = 0.00000000001;
    if (*num2 > *num1) {
        return -1;
    }
    else if (*num1 > *num2) {
        return 1;
    }
    else if (fabs(*num1 - *num2) < eps) {
        return 0;
    }
    return 0;
}

double MyAtof(const char* arr) {
    double val = 0;
    int after_dot = 0;
    double scale = 1;
    int neg = 0;

    if (*arr == '-') {
        arr++;
        neg = 1;
    }

    while (*arr) {
        if (after_dot) {
            scale /= 10;
            val += (*arr - '0') * scale;
        } else {
            if (*arr == '.') {
                after_dot++;
            } else {
                val = val * 10.0 + (*arr - '0');
            }
        }
        arr++;
    }

    return neg ? -val : val;
}


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

