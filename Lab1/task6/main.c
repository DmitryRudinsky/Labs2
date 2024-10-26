#include "options.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect input! Use the format: epsilon\n");
        return 0;
    }

    if (!CheckIsEpsilon(argv[1])) {
        printf("Incorrect input! You can specify epsilon as double (example: 0.001) or in epsilon format (example: 1e-3)\n");
        return 0;
    }

    double eps = MyAtof(argv[1]);
    int precision = 10;

    printf("Результат для интеграла a: %.*f\n", precision, IntegralA(eps));
    printf("Результат для интеграла b: %.*f\n", precision, IntegralB(eps));
    printf("Результат для интеграла c: %.*f\n", precision, IntegralC(eps));
    printf("Результат для интеграла d: %.*f\n", precision, IntegralD(eps));

    return 0;
}
