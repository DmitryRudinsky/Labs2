#include "options.h"

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

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            ++i;
            Swap(&array[i], &array[j]);
        }
    }
    Swap(&array[i + 1], &array[high]);
    return i + 1;
}

void QuickSort(int* array, int low, int high) {
    if (low < high) {
        int pi = Partition(array, low, high);

        QuickSort(array, low, pi - 1);
        QuickSort(array, pi + 1, high);
    }
}

int BinarySearchClosest(const int* array, int size, int element) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == element) {
            return array[mid];
        } else if (array[mid] < element) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left > 0 && abs(array[left - 1] - element) < abs(array[left] - element)) {
        return array[left - 1];
    } else {
        return array[left];
    }
}

int SearchForClosestElement(int element, const int* array, int size) {
    return BinarySearchClosest(array, size, element);
}

int CreateCArray(int** c, const int* a, int* b, int size_a, int size_b) {
    QuickSort(b, 0, size_b - 1);

    *c = (int*)malloc(size_a * sizeof(int));
    if (*c == NULL) {
        return kNoMemory;
    }

    for (int i = 0; i < size_a; ++i) {
        (*c)[i] = a[i] + SearchForClosestElement(a[i], b, size_b);
    }

    return kSuccess;
}

int CreateArrays(int** a, int** b, int* size_a, int* size_b) {
    int a_min = 10, b_min = 10000;
    int range_min = -1000, range_max = 1000;
    *size_a = (rand() % (b_min - a_min + 1)) + a_min;
    *size_b = (rand() % (b_min - a_min + 1)) + a_min;

    *a = (int*)malloc(*size_a * sizeof(int));
    if (*a == NULL) {
        return kNoMemory;
    }

    *b = (int*)malloc(*size_b * sizeof(int));
    if (*b == NULL) {
        free(*a);
        return kNoMemory;
    }

    for (int i = 0; i < *size_a; ++i) {
        (*a)[i] = (rand() % (range_max - range_min + 1)) + range_min;
    }

    for (int i = 0; i < *size_b; ++i) {
        (*b)[i] = (rand() % (range_max - range_min + 1)) + range_min;
    }

    return kSuccess;
}

int ChangeMinAndMax(int array[], int size) {
    if (size == 1) return kOneElementArray;

    int min = array[0], max = array[0];
    int min_index = 0, max_index = 0;

    for (int i = 1; i < size; ++i) {
        if (array[i] < min) {
            min = array[i];
            min_index = i;
        }
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
    }

    array[min_index] = max;
    array[max_index] = min;
    return kSuccess;
}

void PrintArray(const int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
        if ((i % 20 == 0) && i != 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void MakeRandomArray(int array[], int size, int a, int b) {
    for (int i = 0; i < size; ++i) {
        array[i] = (rand() % (b - a + 1)) + a;
    }
}

int CheckValidSize(const char* size) {
    int length = strlen(size);
    if (length < 1 || !IsDigit(size)) {
        return kIncorrectConsoleInput;
    }
    return MyAtoi(size) > 0 ? kSuccess : kIncorrectConsoleInput;
}

void PrintMenu() {
    printf("____________________________________\n");
    printf("\tMENU\n");
    printf("Please input the size of array: ");
}

int IsDigit(const char* number) {
    if (strcmp(number, "-") == 0) return 0;
    if (*number == '-') ++number;

    while (*number != '\0') {
        if (!isdigit(*number)) return 0;
        ++number;
    }
    return 1;
}

int ValidateInput(const char* min, const char* max) {
    int min_length = strlen(min);
    if (min_length < 1 || !IsDigit(min) || !IsDigit(max) || MyAtoi(min) > MyAtoi(max)) {
        return kIncorrectInput;
    }
    return kSuccess;
}

void PrintError(int error) {
    switch (error) {
        case kIncorrectInput:
            printf("\nIncorrect input! Please use the format: ./program A B\n");
            printf("A and B should be integers, with A <= B.\n");
            break;
        case kIncorrectConsoleInput:
            printf("\nIncorrect input! Please input a valid integer.\n");
            break;
        case kOneElementArray:
            printf("\nArray has only one element, min and max cannot be swapped.\n");
            break;
        case kNoMemory:
            printf("\nMemory allocation failed.\n");
            break;
    }
}

int GetString(char** input_string) {
    char temp[128];
    if (scanf("%127s", temp) != 1) {
        return kIncorrectConsoleInput;
    }

    *input_string = (char*)malloc(strlen(temp) + 1);
    if (*input_string == NULL) {
        return kNoMemory;
    }

    strcpy(*input_string, temp);
    return kSuccess;
}