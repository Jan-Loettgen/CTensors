
#include <stdlib.h>
#include "tensor_2d.h"

static double _relu(double d){
    if (d< 0.0){
        return 0.0;
    }
    else {
        return d;
    }
}

int relu(tensor_2d* mat, tensor_2d* mat_out){
    if (mat==NULL || mat_out == NULL){
        return 1;
    }
    if (mat->n_cols != mat_out->n_cols|| mat->n_rows != mat_out->n_rows){
        return 2;
    }
    mat_apply_func(&_relu, mat, mat_out);
    return 0;

}

int linear(tensor_2d* mat, tensor_2d* mat_out){
    if (mat==NULL || mat_out == NULL){
        return 1;
    }
    if (mat->n_cols != mat_out->n_cols|| mat->n_rows != mat_out->n_rows){
        return 2;
    }

    mat_copy(mat, mat_out);
    return 0;
}
