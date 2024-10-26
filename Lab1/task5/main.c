#include "options.h"

int main(int argc, char* argv[]) {
    if (argc > 3) {
        printf("Too many arguments\n");
        return 0;
    }
    if (argc < 3) {
        printf("Too few arguments\n");
        return 0;
    }
    if (!IsDouble(argv[1])) {
        printf("Epsilon must be float and positive\n");
        return 0;
    }
    if (!IsDouble(argv[2])) {
        printf("x must be float and positive\n");
        return 0;
    }

    double epsilon = MyAtof(argv[1]);
    double x = MyAtof(argv[2]);

    printf("Summ A = %f\n", SummA(epsilon, x));
    printf("Summ B = %f\n", SummB(epsilon, x));

    if (fabs(x) >= 1) {
        printf("x must be < 1 for third and fourth summ\n");
    } else {
        printf("Summ C = %f\n", SummC(epsilon, x));
        printf("Summ D = %f\n", SummD(epsilon, x));
    }

    return 0;
}
