#include <stdio.h>
#include <stdlib.h>
#include "options.h"

int main(int argc, char *argv[]) {
    if (!FlagValidation(argv[1])) {
        printf("Wrong flag detected\n");
        return 1;
    }

    char flag = argv[1][1];
    if (!ArgumentsAmountValidation(flag, argc)) {
        printf("Wrong amount of arguments\n");
        return 2;
    }

    double epsilon;
    if (flag == 'q' || flag == 't') {
        for (int i = 2; i < argc; i++) {
            if (!RealNumberValidation(argv[i])) {
                printf("Wrong number detected\n");
                return 3;
            }
        }
        epsilon = MyAtof(argv[2]);
        if (epsilon <= 0) {
            printf("Epsilon must be positive\n");
            return 3;
        }
    } else
    {
        for (int i = 2; i < 4; i++)
        {
            if (!IntegerNumberValidation(argv[i]))
            {
                printf("Wrong number detected\n");
                return 3;
            }
        }
    }

    switch (flag) {
        case 'q': {
            epsilon = MyAtof(argv[2]);
            double *coefficients = (double *)malloc(sizeof(double) * 3);
            if (!coefficients)
            {
                printf("Allocation error\n");
                return 4;
            }

            double *roots = (double *)malloc(sizeof(double) * 2);
            if (!roots) {
                printf("Allocation error\n");
                free(coefficients);
                return 4;
            }

            for (int i = 3; i < 6; i++) {
                coefficients[i - 3] = MyAtof(argv[i]);
            }
            qsort(coefficients, 3, sizeof(double), (int (*)(const void *, const void *))Comp);
            do {
                printf("Roots of equation %fx^2 + %fx + %f:\n", coefficients[0], coefficients[1], coefficients[2]);
                int roots_amount = EquationsRoots(roots, coefficients, epsilon);
                if (roots_amount == -1) {
                    printf("It is not an equation\n");
                } else if (roots_amount == 2) {
                    printf("%f\n%f\n", roots[0], roots[1]);
                } else if (roots_amount == 1) {
                    printf("%f\n", roots[0]);
                } else if (roots_amount == 0) {
                    printf("This equation has no real roots\n");
                }
            } while (Permutations(coefficients, 3, epsilon));

            free(coefficients);
            free(roots);
            break;
        }
        case 'm': {
            int number1 = MyAtoi(argv[2]);
            int number2 = MyAtoi(argv[3]);
            if (number2 == 0) {
                printf("Division by zero error\n");
                return 5;
            }
            if (number1 % number2 == 0) {
                printf("The first number is a multiple of the second\n");
            } else {
                printf("The first number is not a multiple of the second\n");
            }
            break;
        }
        case 't': {
            epsilon = MyAtof(argv[2]);
            double a = MyAtof(argv[3]);
            double b = MyAtof(argv[4]);
            double c = MyAtof(argv[5]);
            if (Triangle(a, b, c, epsilon)) {
                printf("Parameters can be lengths of triangle\n");
            } else {
                printf("Parameters can not be lengths of triangle\n");
            }
            break;
        }
    }
    return 0;
}
