#ifndef TASK9_OPTIONS_H
#define TASK9_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>


enum Errors {
    kSuccess = 0,
    kIncorrectInput = -1,
    kIncorrectConsoleInput = -2,
    kOneElementArray = -3,
    kNoMemory = -4
};

int MyAtoi(char* str);
void PrintError(int error);
int IsDigit(const char* number);
int ValidateInput(const char* min, const char* max);
int CheckValidSize(const char* size);
void PrintMenu();
void MakeRandomArray(int array[], int size, int a, int b);
void PrintArray(const int array[], int size);
int ChangeMinAndMax(int array[], int size);
int CreateArrays(int** a, int** b, int* size_a, int* size_b);
int CreateCArray(int** c, const int* a, int* b, int size_a, int size_b);
void Swap(int* a, int* b);
int Partition(int* array, int low, int high);
void QuickSort(int* array, int low, int high);
int BinarySearchClosest(const int* array, int size, int element);
int SearchForClosestElement(int element, const int* array, int size);
int GetString(char** input_string);


#endif //TASK9_OPTIONS_H
