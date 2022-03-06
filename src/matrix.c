#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "matrix.h"
#define NUM_THREADS 13


tensor_2d* matrix_make(unsigned int num_rows, unsigned int num_cols) {
    tensor_2d* mat = malloc(sizeof(tensor_2d));

    if (mat == NULL){
        return NULL;
    }

    mat->n_rows = num_rows;
    mat->n_cols = num_cols;
    mat->n_elems = num_rows*num_cols;

    double* data = malloc(num_rows*num_cols*sizeof(double));

    if (data == NULL){
        free(mat);
        return NULL;
    }

    mat->data = data;
    return mat;
}

void matrix_free(tensor_2d** mat_ptr){
    free((*mat_ptr)->data);
    free(*mat_ptr);

    *mat_ptr = NULL;
}

tensor_2d* matrix_zeros(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = matrix_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (long i=0; i < (mat->n_elems); i++){
        mat->data[i] = 0.0;
    }
    return mat;
}

tensor_2d* matrix_rand(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = matrix_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (long i=0; i < (mat->n_elems); i++){
        mat->data[i] = rand() /2147483647.0;
    }
    return mat;
}

void matrix_print(tensor_2d* mat){
    if (mat==NULL){
        return;
    }
    printf("\n");
    for (long i=0; i< (mat->n_elems); i++){
        printf("%f\t", mat->data[i]);
        if ((i+1) % mat->n_cols == 0){
            printf("\n");
        }
    }
}

tensor_2d* matrix_add(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b == NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = matrix_make(mat_a->n_cols, mat_a->n_rows);
    if (mat_out == NULL) {
        return NULL;
    }

    for (long i=0; i< (mat_out->n_elems); i++){
        mat_out->data[i] = mat_a->data[i] + mat_b->data[i];
    }
    return mat_out;
}

tensor_2d* matrix_add_T(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b ==NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = matrix_make(mat_a->n_cols, mat_a->n_rows);
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

void* array_add(void* args_ptr){
    array_op_args* args = (array_op_args*)args_ptr;
    double* arr_1 = args->arr_1;
    double* arr_2 = args->arr_2;
    double* arr_out = args->arr_out;
    unsigned long length = args->length;

    if (arr_1 == NULL || arr_2 == NULL || arr_out == NULL){
        pthread_exit(NULL);
    }
    for (unsigned long i=0; i<length; i++){
        arr_out[i] = arr_1[i] + arr_2[i];
    }   
    pthread_exit(NULL);
}

int main(){

    int size = 337  ;

    tensor_2d* mat1 = matrix_rand(size, size);
    tensor_2d* mat2 = matrix_rand(size, size);
    tensor_2d* mat_d = matrix_add(mat1, mat2);
    tensor_2d* mat_c =  matrix_add_T(mat1, mat2);

    matrix_print(mat1);
    matrix_print(mat2);
    matrix_print(mat_c);
    matrix_print(mat_d);

    matrix_free(&mat1);
    matrix_free(&mat2);
    matrix_free(&mat_c);
    matrix_free(&mat_d);
    return 0;
}