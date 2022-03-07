#ifndef TENSOR_2D_THREADED_H
#define TENSOR_2D_THREADED_H

typedef struct array_op_args{
    double* arr_1;
    double* arr_2;
    double* arr_out;
    unsigned long length;
} array_op_args;

tensor_2d* mat_add_T(tensor_2d* mat_a, tensor_2d* mat_b);

void* array_add(void* args_ptr);

tensor_2d* mat_subtract_T(tensor_2d* mat_a, tensor_2d* mat_b);

void* array_subtract(void* args_ptr);
#endif