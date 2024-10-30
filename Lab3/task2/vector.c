#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <stdarg.h>
#include <math.h>

enum RESULTS
{
    success = 0,
    fail = -1,
    no_memory = -2,
    incorrect_input = -3,
    file_open_error = -4
};

int norm_function(Vector_array * max_result, Vector_array * p_result, Vector_array * matrix_result,
                  double (*max_norm)(Vector_ptr vector), double (p_norm)(Vector_ptr vector, int p_arg), int p,
                  double (*matrix_norm)(Vector_ptr vector, double ** matrix_arg), double ** matrix, int size, int quantity, ...)
{
    if (p < 1) return incorrect_input;

    Vector_array all_vectors = (Vector_array)malloc(size * sizeof(Vector_ptr));
    if (!all_vectors) return no_memory;

    va_list vectors;
    va_start(vectors, quantity);

    double norm_max = 0, norm_p = 0, norm_matrix = 0;
    double tmp;
    int result;
    int flag = 0;

    double eps = 0.000000001;
    for (int i = 0; i < quantity; ++i)
    {
        all_vectors[i] = va_arg(vectors, Vector_ptr);
        if ((all_vectors[i] -> size) != size)
        {
            delete_vectors_array(all_vectors, i + 1);
            return incorrect_input;
        }
        tmp = max_norm(all_vectors[i]);
        if (fabs(norm_max - tmp) < eps || (tmp - norm_max) > eps)
        {
            norm_max = tmp;

            if (fabs(norm_max - tmp) < eps) flag = 0;
            else flag = 1;
            result = get_max_norm(flag, max_result, all_vectors[i], size);
            if (result != success)
            {
                delete_vectors_array(all_vectors, i + 1);
                return no_memory;
            }
        }
        tmp = p_norm(all_vectors[i], p);
        if (fabs(norm_p - tmp) < eps || (tmp - norm_p) > eps)
        {
            norm_p = tmp;
            if (fabs(norm_p - tmp) < eps) flag = 0;
            else flag = 1;
            result = get_max_norm(flag, p_result, all_vectors[i], size);
            if (result != success)
            {
                delete_vectors_array(all_vectors, i + 1);
                free(max_result);
                max_result = NULL;
                return no_memory;
            }
        }
        tmp = matrix_norm(all_vectors[i], matrix);
        if (fabs(norm_matrix - tmp) < eps || (tmp - norm_matrix) > eps)
        {
            norm_matrix = tmp;
            if (fabs(norm_matrix - tmp) < eps) flag = 0;
            else flag = 1;
            result = get_max_norm(flag, matrix_result, all_vectors[i], size);
            if (result != success)
            {
                delete_vectors_array(all_vectors, i + 1);
                free(max_result);
                max_result = NULL;
                free(p_result);
                p_result = NULL;
                return no_memory;
            }
        }
    }
    free(all_vectors);
    all_vectors = NULL;
    va_end(vectors);
    return success;
}

int get_max_norm(int flag, Vector_array * result, Vector_ptr vector, int size)
{
    if (*result == NULL)
    {
        *result = (Vector_array)calloc(size, sizeof(Vector_ptr));
        if (!(*result)) return no_memory;
        (*result)[0] = vector;
        return success;
    }
    int i = 0;
    switch (flag)
    {
        case 1:
            while ((*result)[i] != NULL) i++;

            (*result)[i] = vector;
            break;
        case 0:
            while ((*result)[i] != NULL)
            {
                (*result)[i] = NULL;
                i++;
            }
            (*result)[0] = vector;
            break;
        default: break;
    }

    return success;
}

void delete_vectors_array(Vector_array vectors, int size)
{
    if (vectors == NULL) return;
    for (int i = 0; i < size; ++i)
    {
        delete_vector(vectors[i]);
    }
    free(vectors);
    vectors = NULL;
    return;
}

Vector_ptr create_vector(int size, ...)
{
    va_list coords;
    va_start(coords, size);

    double * coordinates = (double*)malloc(size * sizeof(double));
    if (!coordinates) return NULL;

    for (int i = 0; i < size; ++i) coordinates[i] = va_arg(coords, double);

    va_end(coords);

    Vector_ptr vector = (Vector_ptr)malloc(sizeof(Vector));
    if (!vector)
    {
        free(coordinates);
        coordinates = NULL;
        return NULL;
    }

    vector -> size = size;
    vector -> coordinates = coordinates;
    return vector;
}

Vector_ptr create_vector_with_list(int size, double * coords)
{

    double * coordinates = (double*)malloc(size * sizeof(double));
    if (!coordinates) return NULL;

    for (int i = 0; i < size; ++i) coordinates[i] = coords[i];


    Vector_ptr vector = (Vector_ptr)malloc(sizeof(Vector));
    if (!vector)
    {
        free(coordinates);
        coordinates = NULL;
        return NULL;
    }

    vector -> size = size;
    vector -> coordinates = coordinates;
    return vector;
}

int get_size(Vector_array vectors)
{
    int size = 0;
    while (vectors[size] != NULL) size++;
    return size;
}

void delete_vector(Vector_ptr vector)
{
    free(vector -> coordinates);
    vector -> coordinates = NULL;
    free(vector);
    vector = NULL;
    return;
}

void print_vector(Vector_ptr vector)
{
    printf("coordinates: ( ");
    for (int i = 0; i < vector -> size; ++i)
    {
        printf("%lf", (vector -> coordinates)[i]);
        if (i != vector -> size - 1) printf(", ");
    }
    printf(" )\n");
}

double max_norm(Vector_ptr vector)
{
    double eps = 0.00001;
    double max = fabs((vector -> coordinates)[0]);
    double tmp;
    for (int i = 0; i < vector -> size; ++i)
    {
        tmp = fabs((vector -> coordinates)[i]);
        if (tmp - max > eps) max = tmp;
    }
    return max;
}

double p_norm(Vector_ptr vector, int p)
{
    double result = 0;
    for (int i = 0; i < vector -> size; ++i)
    {
        result += quick_pow((vector -> coordinates)[i], p);
    }
    result = pow(result, 1.0 / ((double) p)); // обычное пов, потому что в быстром степень только int
    return result;
}

double matrix_norm(Vector_ptr vector, double ** matrix)
{
    int size = vector -> size;
    double result = 0;
    double tmp = 0;
    for (int i = 0; i < size; ++i) // номер строки матрицы
    {
        for (int j = 0; j < size; ++j) // элемент вектора и элемент в строке матрицы
        {
            tmp += (vector -> coordinates)[j] * matrix[i][j];
        }
        result += tmp * (vector -> coordinates)[i];
        tmp = 0;
    }
    result = sqrt(result);
    return result;
}

double quick_pow(double number, int power)
{
    double eps = 0.0000001;
    if (power > -eps && power < eps) return 1.0;
    if (number > -eps && number < eps) return number;

    double temp;
    if (power % 2 == 0)
    {
        temp = quick_pow(number, power / 2);
        return temp * temp;
    }
    else if (power > 0)
    {
        temp = quick_pow(number, power / 2);
        return temp * temp * number;
    }
    else
    {
        temp = quick_pow(number, (-power)/2);
        return 1.0 / (temp * temp * number);
    }
}
