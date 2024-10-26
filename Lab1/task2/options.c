#include "options.h"


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



int IsPositiveDigit(char *number) {
    if (*number == '-') {
        return 0;
    }
    while (*number != '\0') {
        if (!(*number >= '0' && *number <= '9')) return 0;
        number++;
    }
    return 1;
}

int IsDouble(char *number) {
    int c = 0;
    if (*number == '-') {
        return 0;
    }
    while (*number != '\0') {
        if (*number == '.') {
            if (c == 0) {
                c += 1;
            } else {
                return 0;
            }
        } else if (!(*number >= '0' && *number <= '9')) {
            return 0;
        }
        number++;
    }
    return 1;
}

int IsEpsilonRepresentation(char *eps) {
    int length = strlen(eps);
    if (length < 4) {
        return 0;
    }
    if (eps[0] != '1' || eps[1] != 'e' || eps[2] != '-') {
        return 0;
    }
    for (int i = 3; i < length; ++i) {
        if (!(eps[i] >= '0' && eps[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

int CheckIsEpsilon(char *eps) {
    if (IsDouble(eps)) {
        return 1;
    }
    if (IsEpsilonRepresentation(eps)) {
        return 1;
    }
    return 0;
}

double Factorial(double number) {
    if (number == 0) {
        return 1;
    }
    double result = 1;
    for (int i = 1; i < number + 1; ++i) {
        result *= i;
    }
    return result;
}

double FindELimit(double eps) {
    double n = 1;
    double preres = pow(1 + 1 / n, n);
    double res = pow(1 + 1 / (n + 1), n + 1);
    while (eps < fabs(res - preres)) {
        n += 1;
        preres = res;
        res = pow(1 + 1 / (n + 1), n + 1);
    }
    return preres;
}

double FindERow(double eps) {
    double res = 0;
    double n = 0;
    double preres = 1 / Factorial(n);
    do {
        res += preres;
        n += 1;
        preres = 1 / Factorial(n);
    } while (eps < preres);
    return preres + res;
}

double FindEFunction(double eps) {
    double preres, res = 1;
    do {
        preres = (-1) * (log(res) - 1) * res;
        res += preres;
    } while (eps < fabs(preres));
    return res;
}

double FindPiLimit(double eps) {
    double n = 1;
    double preres = 0;
    double res = 4.0;
    do {
        preres = res;
        res *= (4 * (n + 1) * n) / pow(2 * n + 1, 2);
        n++;
    } while (eps < fabs(res - preres));
    return preres;
}

double FindPiRow(double eps) {
    double res = 0;
    double n = 1;
    double preres = 0;
    do {
        preres = (pow(-1, n - 1)) / (2 * n - 1);
        res += preres;
        n += 1;
    } while (eps < fabs(preres));
    return 4 * res;
}

double FindPiFunction(double eps) {
    double preres, res = 1;
    do {
        preres = (cos(res) + 1) / sin(res);
        res += preres;
    } while (eps < fabs(preres));
    return res;
}

double FindLn2Limit(double eps) {
    double n = 1;
    double preres, res = 0;
    do {
        preres = res;
        res = n * (pow(2, 1 / n) - 1);
        n++;
    } while (eps < fabs(res - preres));
    return res;
}

double FindLn2Row(double eps) {
    double n = 1;
    double preres, res = 0;
    do {
        preres = (pow(-1, n - 1)) / n;
        res += preres;
        n += 1;
    } while (eps < fabs(preres));
    return res;
}

double FindLn2Function(double eps) {
    double preres, res = 1;
    do {
        preres = (-1) * (exp(res) - 2) / exp(res);
        res += preres;
    } while (eps < fabs(preres));
    return res;
}

double FindSqrt2Limit(double eps) {
    int n = 0;
    double res = -0.5;
    double preres = 0;
    while (eps < fabs(res - preres)) {
        n += 1;
        preres = res;
        res = preres - pow(preres, 2) / 2 + 1;
    }
    return res;
}

double FindSqrt2Row(double eps) {
    double n = 0;
    double power = 0.25;
    double res = pow(2, power);
    double preres;
    do {
        preres = res;
        power *= 0.5;
        res *= pow(2, power);
        n += 1;
    } while (eps < fabs(res - preres));
    return res;
}

double FindSqrt2Function(double eps) {
    double preres, res = 1;
    do {
        preres = (-1) * (pow(res, 2) - 2) / (2 * res);
        res += preres;
    } while (eps < fabs(preres));
    return res;
}

double FindC(double n, double k) {
    double result = 1;
    for (double i = k + 1; i < n + 1; ++i) {
        result *= i;
    }
    return result / Factorial(n - k);
}

double FindGammaLimit(double eps) {
    eps = 0.01;
    int m = 2;
    double preres = 0;
    double res = 0;
    double sum;
    double fact;
    int c;
    do {
        preres = res;
        sum = 0;
        fact = 1;
        for (int i = 1; i < m + 1; ++i) {
            fact *= i;
            c = FindC(m, i);
            sum += (c * pow(-1, i) * log(fact)) / i;
        }
        res = sum;
        m += 1;
    } while (eps < fabs(res - preres));
    return res;
}

double FindGammaRow(double eps) {
    double preres = 0;
    double n = 3;
    eps = 0.0000000000001;
    double res = 0.5;
    double elem = 0;
    do {
        preres = res;
        elem = ((1.0 / pow(floor(sqrt(n)), 2)) - (1.0 / n));
        res += elem;
        if (elem < eps) preres = 0;
        n++;
    } while (eps < fabs(res - preres));
    return (res - (pow(PI, 2) / 6));
}

int CheckPrime(int number) {
    if (number <= 1) return 0;
    for (int i = 2; i <= (int)sqrt(number); ++i) {
        if (number % i == 0) return 0;
    }
    return 1;
}

double PForGamma(int t) {
    double res = 1;
    for (int i = 2; i < t + 1; ++i) {
        if (CheckPrime(i)) {
            res *= (i - 1.0) / i;
        }
    }
    return res;
}

double LimitForGamma(double eps) {
    eps = 0.0001;
    double res, preres = 0;
    int t = 2;
    do {
        preres = res;
        res = log(t) * PForGamma(t);
        t += 1;
    } while (fabs(res - preres) > eps);
    return res;
}

double FindGammaFunction(double eps) {
    double preres, res = 1;
    do {
        preres = (exp(-res) - LimitForGamma(eps)) / (exp(-res));
        res += preres;
    } while (eps < fabs(preres));
    return res;
}

void Menu() {
    printf("\nProgram's menu\n\n");
    printf("1. Find e\n2. Find pi\n3. Find ln2\n4. Find sqrt(2)\n5. Find y\n0. Exit\n\n");
    printf("Please, write the number that indicates the function: ");
}
