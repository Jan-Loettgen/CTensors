
#include <stdlib.h>

typedef struct matrix_2d{
    unsigned int n_rows;
    unsigned int n_cols;
    unsigned int n_elems;
    double* data;

} matrix_2d;


matrix_2d* matrix_2d_make(unsigned int num_rows, unsigned int num_cols) {
    matrix_2d* mat = malloc(sizeof(matrix_2d));

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

    return mat;
}

void matrix_2d_free(matrix_2d** mat_ptr){
    matrix_2d* mat = *mat_ptr;

    free(mat->data);
    free(mat);

    mat = NULL;
}

matrix_2d* matrix_2d_zeros(unsigned int num_rows, unsigned int num_cols){
    matrix_2d* mat = matrix_2d_make(num_rows, num_cols);

    if (mat == NULL){
        retrun NULL;
    }

    for (int i=0; i < (mat->n_elems); i++)
    mat->data[i] = 0.0;
}