#include "options.h"

int main(int argc, char* argv[]) {
    if (argc != 3) return 0;

    int result = ValidateInput(argv[1], argv[2]);
    if (result == kIncorrectInput) {
        PrintError(result);
        return kIncorrectInput;
    }

    PrintMenu();
    char* size_string;
    result = GetString(&size_string);
    if (result == kNoMemory) {
        free(size_string);
        PrintError(result);
        return kNoMemory;
    }

    result = CheckValidSize(size_string);
    while (result == kIncorrectConsoleInput) {
        free(size_string);
        PrintError(kIncorrectConsoleInput);
        PrintMenu();
        result = GetString(&size_string);
        if (result == kNoMemory) {
            free(size_string);
            PrintError(result);
            return kNoMemory;
        }
        result = CheckValidSize(size_string);
    }

    srand(time(NULL));
    int a = MyAtoi(argv[1]);
    int b = MyAtoi(argv[2]);
    int size = MyAtoi(size_string);
    free(size_string);

    printf("\n____________________________________\n");
    printf("\tTASK ONE\n");
    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        PrintError(kNoMemory);
        return kNoMemory;
    }
    MakeRandomArray(array, size, a, b);
    printf("Array with random numbers from %d to %d, size %d:\n", a, b, size);
    PrintArray(array, size);

    result = ChangeMinAndMax(array, size);
    if (result == kOneElementArray) {
        PrintError(result);
    }
    printf("Array after swapping min and max:\n");
    PrintArray(array, size);

    // Task 2
    printf("\n____________________________________\n");
    printf("\tTASK TWO\n");

    int* array_a = NULL;
    int* array_b = NULL;
    int* array_c = NULL;
    int size_a, size_b;

    result = CreateArrays(&array_a, &array_b, &size_a, &size_b);
    if (result == kNoMemory) {
        PrintError(result);
    } else {
        printf("\nArray A (First 15 Elements):\n");
        PrintArray(array_a, 15);
        printf("\nArray B (First 15 Elements):\n");
        PrintArray(array_b, 15);

        result = CreateCArray(&array_c, array_a, array_b, size_a, size_b);
        if (result == kNoMemory) {
            PrintError(result);
        } else {
            printf("\nArray C:\n");
            PrintArray(array_c, size_a);
        }
    }

    free(array);
    free(array_a);
    free(array_b);
    free(array_c);

    printf("\n____________________________________\n");
    printf("\nThe program has finished.\n");
    printf("\n____________________________________\n");
    return 0;
}
