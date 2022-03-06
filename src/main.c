#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

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