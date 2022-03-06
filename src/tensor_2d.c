#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"

tensor_2d* mat_make(unsigned int num_rows, unsigned int num_cols) {
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

void mat_free(tensor_2d** mat_ptr){
    free((*mat_ptr)->data);
    free(*mat_ptr);

    *mat_ptr = NULL;
}

tensor_2d* mat_zeros(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = mat_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (long i=0; i < (mat->n_elems); i++){
        mat->data[i] = 0.0;
    }
    return mat;
}

tensor_2d* mat_rand(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = mat_make(num_rows, num_cols);

    if (mat == NULL){
        return NULL;
    }

    for (long i=0; i < (mat->n_elems); i++){
        mat->data[i] = rand() /2147483647.0;
    }
    return mat;
}

void mat_print(tensor_2d* mat){
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

    for (long i=0; i< (mat_out->n_elems); i++){
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

    for (long i=0; i< (mat_out->n_elems); i++){
        mat_out->data[i] = mat_a->data[i] - mat_b->data[i];
    }
    return mat_out;
}

tensor_2d* matrix_