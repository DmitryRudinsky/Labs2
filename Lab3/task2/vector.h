#ifndef TASK2_VECTOR_H
#define TASK2_VECTOR_H

typedef struct {
    int size;
    double * coordinates;
} Vector, *Vector_ptr, **Vector_array;

int norm_function(Vector_array * max_result, Vector_array * p_result, Vector_array * matrix_result,
                  double (*max_norm)(Vector_ptr vector), double (p_norm)(Vector_ptr vector, int p_arg), int p,
                  double (*matrix_norm)(Vector_ptr vector, double ** matrix_arg), double ** matrix, int size, int quantity, ...);

double max_norm(Vector_ptr vector);
double p_norm(Vector_ptr vector, int p);
double matrix_norm(Vector_ptr vector, double ** matrix);

int get_max_norm(int flag, Vector_array * result, Vector_ptr vector, int size);
double quick_pow(double number, int power);

void delete_vectors_array(Vector_array vectors, int size);
void delete_vector(Vector_ptr vector);

int get_size(Vector_array vectors);

Vector_ptr create_vector(int size, ...);
Vector_ptr create_vector_with_list(int size, double * coords);

void print_vector(Vector_ptr vector);


#endif //TASK2_VECTOR_H
