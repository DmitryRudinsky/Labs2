#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2,
    incorrect_input = -3,
    file_open_error = -4
};

void print_error(int error);
void print_vector_array(Vector_array vectors);

int main()
{
    int size = 3;
    int quantity = 4;
    Vector_ptr v1 = create_vector(size, 1.0, 6.7, 8.12);
    Vector_ptr v2 = create_vector(size, 9.25, 2.0, 3.0);
    Vector_ptr v3 = create_vector(size, 5.06, 8.9, 7.3);
    Vector_ptr v4 = create_vector(size, 3.4, 2.0, 5.0);

    Vector_array max_result = NULL;
    Vector_array matrix_result = NULL;
    Vector_array p_result = NULL;

    int p = 3;
    double ** matrix = (double**)malloc(size * sizeof(double*));
    if (!matrix)
    {
        delete_vector(v1);
        delete_vector(v2);
        delete_vector(v3);
        delete_vector(v4);
        print_error(no_memory);
        return no_memory;
    }
    for (int i = 0; i < size; ++i)
    {
        matrix[i] = (double*)malloc(size * sizeof(double));
        if (!(matrix[i]))
        {
            for (int j = 0; j < i; ++j)
            {
                free(matrix[j]);
                matrix[j] = NULL;
            }
            free(matrix);
            matrix = NULL;
            delete_vector(v1);
            delete_vector(v2);
            delete_vector(v3);
            delete_vector(v4);
            print_error(no_memory);
            return no_memory;
        }
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = 1;
        }
    }
    // единичная матрица
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][2] = 0;
    matrix[2][0] = 0;
    matrix[2][1] = 0;

    int result = norm_function(&max_result, &p_result, &matrix_result, max_norm, p_norm, p, matrix_norm, matrix, size, 4, v1, v2, v3, v4);
    if (result != success)
    {
        for (int j = 0; j < size; ++j)
        {
            free(matrix[j]);
            matrix[j] = NULL;
        }
        free(matrix);
        matrix = NULL;
        delete_vector(v1);
        delete_vector(v2);
        delete_vector(v3);
        delete_vector(v4);
        print_error(result);
        return result;
    }

    printf("For max-norm:\n");
    print_vector_array(max_result);
    printf("\n");
    printf("For p-norm:\n");
    print_vector_array(p_result);
    printf("\n");
    printf("For matrix-norm:\n");
    print_vector_array(matrix_result);
    printf("\n");

    delete_vector(v1);
    delete_vector(v2);
    delete_vector(v3);
    delete_vector(v4);
    free(max_result);
    max_result = NULL;
    free(p_result);
    p_result = NULL;
    free(matrix_result);
    matrix_result = NULL;

    for (int j = 0; j < size; ++j)
    {
        free(matrix[j]);
        matrix[j] = NULL;
    }
    free(matrix);
    matrix = NULL;

    printf("\nProgram has finished correctly.\n");
}

void print_vector_array(Vector_array vectors)
{
    int size = get_size(vectors);
    for (int i = 0; i < size; ++i)
    {
        print_vector(vectors[i]);
    }
}

void print_error(int error)
{
    switch(error)
    {
        case no_memory:
            printf("\nComputer doesnot have enough memory for this calculation.");
            break;
        case incorrect_input:
            printf("\nIncorrect input.\n");
            break;
        case file_open_error:
            printf("\nCannot open file!\n");
            break;
    }
}
