#ifndef C_MATRIX_H
#define C_MATRIX_H

typedef struct matrix_2d{
    unsigned int n_rows;
    unsigned int n_cols;
    unsigned long n_elems;
    double* data;

} matrix_2d;

typedef struct _array_add_args{
    double* arr_1;
    double* arr_2;
    double* arr_out;
    long length;
} _array_add_args;


matrix_2d* matrix_2d_make(unsigned int num_rows, unsigned int num_cols);

void matrix_2d_free(matrix_2d** mat_ptr);

matrix_2d* matrix_2d_zeros(unsigned int num_rows, unsigned int num_cols);

matrix_2d* matrix_2d_rand(unsigned int num_rows, unsigned int num_cols);

void matrix_2d_print(matrix_2d* mat);

matrix_2d* matrix_2d_add(matrix_2d* mat_a, matrix_2d* mat_b);

matrix_2d* matrix_2d_add_T(matrix_2d* mat_a, matrix_2d* mat_b);

void* array_add(void* args_ptr);
#endif