#include <stdlib.h>
#include <stdio.h>

typedef struct tensor_2d{
    unsigned int n_rows; ///< Number of rows in the matrix.
    unsigned int n_cols; ///< Number of columns in the matrix.
    unsigned long n_elems; ///< Total number of elements stored in matrix
    double* data; ///< A pointer to an array of doubles that stores the flattened matrix.

} tensor_2d;



tensor_2d* mat_make_C(unsigned int num_rows, unsigned int num_cols){
    tensor_2d* mat = (tensor_2d*)malloc(sizeof(tensor_2d));

    if (mat == NULL){
        return NULL;
    }

    unsigned long long ull_num_elems = num_rows*num_cols;
    
    //!limit because unsigned long cannot hold a number greater than 4294967295.
    if (ull_num_elems > 4294967295){
        printf("Requested matrix with %lld elements.\n", ull_num_elems);
        printf("Maximum possible number of elements is: %ld\n", 4294967295);
        return NULL;
    }

    unsigned long num_elems = num_rows*num_cols;
    //!limit specfied in #define MAX_NUM_ELEMENTS.
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