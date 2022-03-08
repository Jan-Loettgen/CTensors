#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

double ReLu(double d){
    if (d< 0.0){
        return 0.0;
    }
    else {
        return d;
    }
}

int main(){

    tensor_2d* mat1 = mat_eye(5);
    tensor_2d* mat2 = mat_rand(5, 5);

    tensor_2d* mat_c = mat_subtract_T(mat1, mat2);

    tensor_2d* mat_d = mat_mul_T(mat1, mat2);


    mat_print(mat_c);
    mat_print(mat_d);

    mat_free(&mat1);
    mat_free(&mat2);
    mat_free(&mat_c);
    mat_free(&mat_d);

    printf("\n exiting \n");
    return 0;

}