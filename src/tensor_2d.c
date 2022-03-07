#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "tensor_2d.h"

//corresponds to a matrix of 16384 x 16384, will use 0.25 GB of RAM
#define MAX_NUM_ELEMENTS 268435456

tensor_2d* mat_make(unsigned int num_rows, unsigned int num_cols) {
    tensor_2d* mat = malloc(sizeof(tensor_2d));

    if (mat == NULL){
        return NULL;
    }

    unsigned long long ull_num_elems = num_rows*num_cols;
    //limit because unsigned long cannot hold a number greater than 4294967295.
    if (ull_num_elems > 4294967295){
        printf("Requested matrix with %lld elements.\n", ull_num_elems);
        printf("Maximum possible number of elements is: %ld\n", 4294967295);
        return NULL;
    }

    unsigned long num_elems = num_rows*num_cols;
    //limit specfied in #define MAX_NUM_ELEMENTS 268435456.
    if (num_elems > MAX_NUM_ELEMENTS){
        printf("Requested matrix with %ld elements.\n", num_elems);
        printf("Maximum possible number of elements is: %d\n", MAX_NUM_ELEMENTS);
        return NULL;
    }

    mat->n_elems = num_elems;
    mat->n_rows = num_rows;
    mat->n_cols = num_cols;

    double* data = malloc(num_elems*sizeof(double));

    if (data == NULL){
        free(mat);
        return NULL;
    }

    mat->data = data;
    return mat;
}

void mat_free(tensor_2d** mat_ptr){
    if (*mat_ptr == NULL){
        return;
    }

    free((*mat_ptr)->data);
    free(*mat_ptr);

    *mat_ptr = NULL;
}

tensor_2d* mat_zeros(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = mat_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (unsigned long i=0; i < (mat->n_elems); i++){
        mat->data[i] = 0.0;
    }
    return mat;
}

tensor_2d* mat_rand(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = mat_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (unsigned long i=0; i < (mat->n_elems); i++){
        mat->data[i] = rand() /2147483647.0;
    }
    return mat;
}

tensor_2d* mat_eye(unsigned int num_rows){
    tensor_2d* mat = mat_make(num_rows, num_rows);

    if (mat == NULL){
        return NULL;
    }

    for (unsigned long i=0; i < (mat->n_elems); i++){
        if (i % (num_rows+1) == 0){
            mat->data[i] = 1.0;
        }
        else{
            mat->data[i] = 0.0;
        }
    }
    return mat;
}

void mat_print(tensor_2d* mat){
    if (mat==NULL){
        return;
    }
    printf("\n");
    for (unsigned long i=0; i< (mat->n_elems); i++){
        printf("%f\t", mat->data[i]);
        if ((i+1) % mat->n_cols == 0){
            printf("\n");
        }
    }
}

tensor_2d* mat_add(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b == NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = mat_make(mat_a->n_cols, mat_a->n_rows);
    if (mat_out == NULL) {
        return NULL;
    }

    for (unsigned long i=0; i< (mat_out->n_elems); i++){
        mat_out->data[i] = mat_a->data[i] + mat_b->data[i];
    }
    return mat_out;
}

tensor_2d* mat_subtract(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b == NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_rows != mat_b->n_rows){
        return NULL;
    }

    tensor_2d* mat_out = mat_make(mat_a->n_cols, mat_a->n_rows);
    if (mat_out == NULL) {
        return NULL;
    }

    for (unsigned long i=0; i<(mat_out->n_elems); i++){
        mat_out->data[i] = mat_a->data[i] - mat_b->data[i];
    }
    return mat_out;
}

tensor_2d* mat_mul(tensor_2d* mat_a, tensor_2d* mat_b){
    if (mat_a == NULL || mat_b == NULL){
        return NULL;
    }
    else if (mat_a->n_cols != mat_b->n_rows){
        return NULL;
    }
    tensor_2d* mat_out = mat_zeros(mat_a->n_rows, mat_b->n_cols);
    if (mat_out == NULL) {
        return NULL;
    }

    int mat_index;
    for (unsigned int row=0; row<mat_a->n_rows; row++){
        for (unsigned int col=0; col<mat_b->n_cols; col++){
            mat_index = row*mat_out->n_cols+col;
            for (unsigned int k=0; k<mat_a->n_cols; k++){
                mat_out->data[mat_index] += mat_a->data[(row*mat_a->n_cols)+k]*mat_b->data[(mat_b->n_cols*k)+col];
            }
        }
    }
    return mat_out;
}

tensor_2d* mat_transpose(tensor_2d* mat){
    if (mat == NULL){
        return NULL;
    }

    tensor_2d* mat_out = mat_make(mat->n_cols, mat->n_rows);
    if (mat_out == NULL) {
        return NULL;
    }
    for (unsigned int col= 0; col<mat->n_cols; col++){
        for (unsigned int row =0; row<mat->n_rows; row++){
            mat_out->data[row*mat->n_rows + col] = mat->data[row+col*mat->n_cols];
        }
    }

    return mat_out;
}