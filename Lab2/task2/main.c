#include "options.h"

int main() {
    ErrorCode error;

    double avg = GeometricAverage(&error, 5, 1.0, 2.0, 3.0, 4.0, 5.0);
    if (error == kErrorNone) {
        printf("Geometric average: %f\n", avg);
    } else {
        printf("Error calculating geometric average: %d\n", error);
    }

    printf("Power: %f\n", MyPow(3, 2));

    return 0;
}
