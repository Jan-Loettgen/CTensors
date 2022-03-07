#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

int main(){

    tensor_2d* mat1 = mat_rand(16, 5);
    tensor_2d* mat2 = mat_rand(5, 3);

    //NOTE SEGMENTATION FAULT WHEN row mat A > col MAT B

    tensor_2d* mat_c = mat_mul(mat1, mat2);
    tensor_2d* mat_T = mat_transpose(mat1);


    // mat_print(mat1);
    // mat_print(mat2);
    // mat_print(mat_c);
    // mat_print(mat_T);

    mat_free(&mat1);
    mat_free(&mat2);
    mat_free(&mat_c);
    mat_free(&mat_T);

    printf("\n exiting \n");
    return 0;

}