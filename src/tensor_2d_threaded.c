#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

#define NUM_THREADS 13

tensor_2d* mat_add_T(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b ==NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = mat_make(mat_a->n_cols, mat_a->n_rows);
    if (mat_out == NULL) {
        return NULL;
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
        pthread_create(&(threads[i]), NULL, array_add, args_ptr);
    }

    for (int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    return mat_out;
}

tensor_2d* mat_subtract_T(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b ==NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = mat_make(mat_a->n_cols, mat_a->n_rows);
    if (mat_out == NULL) {
        return NULL;
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
        pthread_create(&(threads[i]), NULL, array_subtract, args_ptr);
    }

    for (int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    return mat_out;
}

tensor_2d* mat_mul_T(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b ==NULL){
        return NULL;
    }
    if (mat_a->n_cols != mat_b->n_rows){
        return NULL;
    }
    tensor_2d* mat_out = mat_zeros(mat_a->n_rows, mat_b->n_cols);
    if (mat_out == NULL) {
        return NULL;
    }

    // if (mat_a->n_rows < NUM_THREADS) {
    //     unsigned int num_threads = mat_a->n_rows;
    // }
    // else{
    //     unsigned int num_threads = NUM_THREADS;
    // }

    pthread_t threads[mat_a->n_rows];
    array_mat_mul_args args_arr[mat_a->n_rows];

    for (unsigned int row=0; row<mat_a->n_rows; row++){
        array_mat_mul_args args;
        args.arr = &(mat_a->data[row*mat_a->n_cols]);
        args.mat = mat_b;
        args.arr_out = &(mat_out->data[row*mat_out->n_cols]);

        args_arr[row] = args;
    }
    //consider combing these later
    for (unsigned int row=0; row<mat_a->n_rows; row++){
        void* args_ptr = &(args_arr[row]);
        pthread_create(&(threads[row]), NULL, array_mat_mul, args_ptr);
    }
    for (unsigned int row=0; row<mat_a->n_rows; row++){
        pthread_join(threads[row], NULL);
    }
    return mat_out;
}

void* array_add(void* args_ptr){
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

void* array_subtract(void* args_ptr){
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

void* array_mat_mul(void* args_ptr){
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
        printf("Last computed double : %f\n",(args->arr_out)[col] );
    }

    return NULL;
}

