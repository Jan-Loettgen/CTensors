#ifndef TENSOR_2D_H
#define TENSOR_2D_H

typedef struct tensor_2d{
    unsigned int n_rows;
    unsigned int n_cols;
    unsigned long n_elems;
    double* data;

} tensor_2d;

tensor_2d* mat_make(unsigned int num_rows, unsigned int num_cols);

void mat_free(tensor_2d** mat_ptr);

tensor_2d* mat_zeros(unsigned int num_rows, unsigned int num_cols);

tensor_2d* mat_rand(unsigned int num_rows, unsigned int num_cols);

tensor_2d* mat_eye(unsigned int num_rows);

void mat_print(tensor_2d* mat);

tensor_2d* mat_add(tensor_2d* mat_a, tensor_2d* mat_b);

tensor_2d* mat_subtract(tensor_2d* mat_a, tensor_2d* mat_b);

tensor_2d* mat_mul(tensor_2d* mat_a, tensor_2d* mat_b);

tensor_2d* mat_transpose(tensor_2d* mat);

tensor_2d* mat_apply_func(double (func)(double d), tensor_2d* mat);

#endif