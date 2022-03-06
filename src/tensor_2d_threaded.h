#ifndef TENSOR_2D_THREADED_H
#define TENSOR_2D_THREADED_H

typedef struct array_op_args{
    double* arr_1;
    double* arr_2;
    double* arr_out;
    long length;
} array_op_args;

tensor_2d* matrix_add_T(tensor_2d* mat_a, tensor_2d* mat_b);

void* array_add(void* args_ptr);
#endif