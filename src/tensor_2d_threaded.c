#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

#define NUM_THREADS 13

typedef struct array_op_args{
    double* arr_1;
    double* arr_2;
    double* arr_out;
    unsigned long length;
} array_op_args;

typedef struct array_mat_mul_args{
    double* arr;
    tensor_2d* mat;
    double* arr_out;
}array_mat_mul_args;

static void* array_add(void* args_ptr){
    array_op_args* args = (array_op_args*)args_ptr;
    double* arr_1 = args->arr_1;
    double* arr_2 = args->arr_2;
    double* arr_out = args->arr_out;
    unsigned long length = args->length;

    if (arr_1 == NULL || arr_2 == NULL || arr_out == NULL){
        return NULL;
    }
    for (unsigned long i=0; i<length; i++){
        arr_out[i] = arr_1[i] + arr_2[i];
    }   
    return NULL;
}

static void* array_sub(void* args_ptr){
    array_op_args* args = (array_op_args*)args_ptr;
    double* arr_1 = args->arr_1;
    double* arr_2 = args->arr_2;
    double* arr_out = args->arr_out;
    unsigned long length = args->length;

    if (arr_1 == NULL || arr_2 == NULL || arr_out == NULL){
        return NULL;
    }

    for (unsigned long i=0; i<length; i++){
        arr_out[i] = arr_1[i] - arr_2[i];
    }   
    return NULL;
}

int mat_sub_T(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL|| mat_out == NULL){
        return 1;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_cols != mat_out->n_cols){
        return 2;
    }
    else if (mat_a->n_rows != mat_b->n_rows || mat_a->n_rows != mat_out->n_rows){
        return 2;
    }
    pthread_t threads[NUM_THREADS];
    int batch = mat_a->n_elems/NUM_THREADS;
    array_op_args args_arr[NUM_THREADS];

    for (int i=0; i<NUM_THREADS; i++){
        array_op_args args;
        args.arr_1 = mat_a->data + i*batch;
        args.arr_2 = mat_b->data + i*batch;
        args.arr_out = mat_out->data+ i*batch;
        if (i == NUM_THREADS-1){
            args.length = batch+mat_a->n_elems%NUM_THREADS;
        }
        else{
        args.length = batch;
        }
        args_arr[i] = args;
    }

    for (int i=0; i<NUM_THREADS; i++){
        void* args_ptr = &(args_arr[i]);
        pthread_create(&(threads[i]), NULL, array_sub, args_ptr);
    }

    for (int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}


static void* array_mat_mul(void* args_ptr){
    array_mat_mul_args* args = (array_mat_mul_args*) args_ptr;

    if (args == NULL) {
        return NULL;
    }
    if (args->arr == NULL ||args->mat == NULL|| args->arr_out == NULL){
        return NULL;
    }
    for (unsigned int col = 0; col< args->mat->n_cols; col++){
        (args->arr_out)[col] = 0.0;
        for (unsigned int i = 0; i < args->mat->n_rows; i++) {
            (args->arr_out)[col] += args->arr[i] * args->mat->data[col + i*args->mat->n_cols];
        }
    }

    return NULL;
}

int mat_mul_T(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL || mat_out == NULL){
        return 1;
    }
    if (mat_a->n_cols != mat_b->n_rows){
        return 2;
    }
    if (mat_out->n_rows != mat_a->n_rows || mat_out->n_cols != mat_b->n_cols){
        return 2;
    }

    pthread_t threads[mat_a->n_rows];
    array_mat_mul_args args_arr[mat_a->n_rows];

    for (unsigned int row=0; row<mat_a->n_rows; row++){
        array_mat_mul_args args;
        args.arr = &(mat_a->data[row*mat_a->n_cols]);
        args.mat = mat_b;
        args.arr_out = &(mat_out->data[row*mat_out->n_cols]);

        args_arr[row] = args;
    }

    if (mat_a->n_rows < NUM_THREADS) {
        unsigned int num_threads = mat_a->n_rows;
    }
    else{
        unsigned int num_threads = NUM_THREADS;
    }

    int active_threads = 0;

    for (unsigned int row=0; row<mat_a->n_rows; row++){


        if active_threads
        void* args_ptr = &(args_arr[row]);
        pthread_create(&(threads[row]), NULL, array_mat_mul, args_ptr);
    }
    for (unsigned int row=0; row<mat_a->n_rows; row++){
        pthread_join(threads[row], NULL);
    }
    return 0;
}
