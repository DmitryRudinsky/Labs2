#include <stdio.h>
#include "options.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || !CheckIsEpsilon(argv[1])) {
        printf("The program input is incorrect.\nTry to run the program again using input format: 'epsilon'.");
        return 0;
    }
    double eps = MyAtof(argv[1]);
    char l_temp[10];
    printf("Write the number of symbols after comma: ");

    scanf("%s", l_temp);
    while (IsPositiveDigit(l_temp) == 0) {
        printf("Incorrect input. Try again.\n");
        printf("Write the number of symbols after comma: ");
        scanf("%s", l_temp);
        printf("\n");
    }
    int l = MyAtoi(l_temp);
    int state = 9;
    char state_temp[10];
    while (state != 0) {
        Menu();
        scanf("%s", state_temp);
        printf("\n");
        while (!IsPositiveDigit(state_temp)) {
            printf("\nIncorrect input! Try again.\n");
            printf("Please, write the number that indicates the function: ");
            scanf("%s", state_temp);
            printf("\n");
        }
        state = MyAtoi(state_temp);
        double result;
        switch (state) {
            case 1:
                result = FindELimit(eps);
                printf("\nLimit calculation for e: %.*f\n", l, result);
                result = FindERow(eps);
                printf("\nRow calculation for e: %.*f\n", l, result);
                result = FindEFunction(eps);
                printf("\nFunction calculation for e: %.*f\n", l, result);
                break;
            case 2:
                result = FindPiLimit(eps);
                printf("\nLimit calculation for pi: %.*f\n", l, result);
                result = FindPiRow(eps);
                printf("\nRow calculation for pi: %.*f\n", l, result);
                result = FindPiFunction(eps);
                printf("\nFunction calculation for pi: %.*f\n", l, result);
                break;
            case 3:
                result = FindLn2Limit(eps);
                printf("\nLimit calculation for ln2: %.*f\n", l, result);
                result = FindLn2Row(eps);
                printf("\nRow calculation for ln2: %.*f\n", l, result);
                result = FindLn2Function(eps);
                printf("\nFunction calculation for ln2: %.*f\n", l, result);
                break;
            case 4:
                result = FindSqrt2Limit(eps);
                printf("\nLimit calculation for sqrt(2): %.*f\n", l, result);
                result = FindSqrt2Row(eps);
                printf("\nRow calculation for sqrt(2): %.*f\n", l, result);
                result = FindSqrt2Function(eps);
                printf("\nFunction calculation for sqrt(2): %.*f\n", l, result);
                break;
            case 5:
                result = FindGammaLimit(eps);
                printf("\nLimit calculation for gamma: %.*f\n", l, result);
                result = FindGammaRow(eps);
                printf("\nRow calculation for gamma: %.*f\n", l, result);
                result = FindGammaFunction(eps);
                printf("\nFunction calculation for gamma: %.*f\n", l, result);
                break;
            case 0:
                return 0;
        }
    }
}
