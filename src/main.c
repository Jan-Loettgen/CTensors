#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

int main(){

    int size = 17000;

    tensor_2d* mat1 = mat_rand(size, size);
    tensor_2d* mat2 = mat_rand(size, size);

    tensor_2d* mat_c = mat_mul(mat1, mat2);

    mat_print(mat1);
    mat_print(mat2);
    mat_print(mat_c);

    mat_free(&mat1);
    mat_free(&mat2);
    mat_free(&mat_c);
    return 0;

}