#ifndef C_MATRIX_H
#define C_MATRIX_H

typedef struct tensor_2d{
    unsigned int n_rows;
    unsigned int n_cols;
    unsigned long n_elems;
    double* data;

} tensor_2d;

typedef struct array_op_args{
    double* arr_1;
    double* arr_2;
    double* arr_out;
    long length;
} array_op_args;


tensor_2d* matrix_make(unsigned int num_rows, unsigned int num_cols);

void matrix_free(tensor_2d** mat_ptr);

tensor_2d* matrix_zeros(unsigned int num_rows, unsigned int num_cols);

tensor_2d* matrix_rand(unsigned int num_rows, unsigned int num_cols);

void matrix_print(tensor_2d* mat);

tensor_2d* matrix_add(tensor_2d* mat_a, tensor_2d* mat_b);

tensor_2d* matrix_add_T(tensor_2d* mat_a, tensor_2d* mat_b);

void* array_add(void* args_ptr);
#endif