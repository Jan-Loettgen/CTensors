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
    //limit specfied in #define MAX_NUM_ELEMENTS.
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

int mat_free(tensor_2d** mat_ptr){
    if (*mat_ptr == NULL){
        return 1;
    }

    free((*mat_ptr)->data);
    free(*mat_ptr);

    *mat_ptr = NULL;

    return 0;
}

int mat_zeros(tensor_2d* mat_out){
    if (mat_out == NULL){
        return 1;
    }

    for (unsigned long i=0; i < (mat_out->n_elems); i++){
        mat_out->data[i] = 0.0;
    }
    return 0;
}

int mat_rand(double low, double high, tensor_2d* mat_out){
    if (mat_out == NULL){
        return 1;
    }

    for (unsigned long i=0; i < (mat_out->n_elems); i++){
        mat_out->data[i] = low + (high-low)*(rand()/2147483647.0);
    }
    return 0;
}

int mat_eye(tensor_2d* mat_out){
 if (mat_out == NULL){
        return 1;
    }

    for (unsigned long i=0; i < (mat_out->n_elems); i++){
        if (i % (mat_out->n_rows+1) == 0){
            mat_out->data[i] = 1.0;
        }
        else{
            mat_out->data[i] = 0.0;
        }
    }
    return 0;
}

int mat_print(tensor_2d* mat){
    if (mat==NULL){
        return 1;
    }
    printf("\n");
    for (unsigned long i=0; i< (mat->n_elems); i++){
        printf("%f\t", mat->data[i]);
        if ((i+1) % mat->n_cols == 0){
            printf("\n");
        }
    }
    return 0;
}

int mat_add(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL|| mat_out == NULL){
        return 1;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_cols != mat_out->n_cols){
        return 2;
    }
    else if (mat_a->n_rows != mat_b->n_rows || mat_a->n_rows != mat_out->n_rows){
        return 2;
    }

    for (unsigned long i=0; i< mat_out->n_elems; i++){
        mat_out->data[i] = mat_a->data[i] + mat_b->data[i];
    }
    return 0;
}

int mat_sub(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL|| mat_out == NULL){
        return 1;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_cols != mat_out->n_cols){
        return 2;
    }
    else if (mat_a->n_rows != mat_b->n_rows || mat_a->n_rows != mat_out->n_rows){
        return 2;
    }

    for (unsigned long i=0; i< mat_out->n_elems; i++){
        mat_out->data[i] = mat_a->data[i] - mat_b->data[i];
    }
    return 0;
}

int mat_mul(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL || mat_out == NULL){
        return 1;
    }
    if (mat_a->n_cols != mat_b->n_rows){
        return 2;
    }
    if (mat_out->n_rows != mat_a->n_rows || mat_out->n_cols != mat_b->n_cols){
        return 2;
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
    return 0;
}

int mat_transpose(tensor_2d* mat, tensor_2d* mat_out){
    if (mat == NULL || mat_out == NULL){
        return 1;
    }
    if (mat->n_rows != mat_out->n_rows || mat->n_cols != mat_out->n_cols){
        return 2;
    }

    for (unsigned int col= 0; col<mat->n_cols; col++){
        for (unsigned int row =0; row<mat->n_rows; row++){
            mat_out->data[row*mat->n_rows + col] = mat->data[row+col*mat->n_cols];
        }
    }

    return 0;
}

int mat_copy(tensor_2d* mat, tensor_2d* mat_out){
    if (mat == NULL || mat_out == NULL){
        return 1;
    }
    if (mat->n_rows != mat_out->n_rows || mat->n_cols != mat_out->n_cols){
        return 2;
    }

    for (unsigned long i = 0; i<mat->n_elems; i++){
        mat_out->data[i] = mat->data[i];
    }

    return 0;

}

int mat_apply_func(double (func)(double d), tensor_2d* mat, tensor_2d* mat_out){
    if (mat == NULL|| func==NULL || mat_out == NULL) {
        return 1;
    }
    if (mat->n_rows != mat_out->n_rows || mat->n_cols != mat_out->n_cols){
        return 2;
    }

    for (unsigned long i = 0; i<mat->n_elems; i++){
        mat_out->data[i] = func(mat->data[i]);
    }

    return 0;
}
int mat_apply_func_2(void (func)(double d, int reset, void* out_var), tensor_2d* mat, void* out_var){
        if (mat == NULL|| func==NULL) {
        return 1;
    }
    for (unsigned long i = 0; i<mat->n_elems; i++){
        if (i == (mat->n_elems-1)){
            func(mat->data[i], 1, out_var);
        }
        else{
            func(mat->data[i], 0, out_var);
        }
    }
    return 0;
}