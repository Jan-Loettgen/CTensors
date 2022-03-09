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

void* Sum_mat(double d, int reset, void* out_var){
    static double sum = 0;
    sum += d;

    if (reset==1){
        *((double*)out_var) = sum;
        sum = 0;
        return NULL;
    }
    else{
        return NULL;
    }
}


int main(){
    tensor_2d* mat1 = mat_rand(5, 9);

    double sum = 0;
    double* sum_ptr = &sum;

    mat_apply_func_2(&Sum_mat, mat1, sum_ptr);
    printf("sum of matrix : %f\n",*sum_ptr);

    tensor_2d* mat2 = mat_rand(5, 5);

    tensor_2d* mat_c = mat_subtract_T(mat1, mat2);

    tensor_2d* mat_d = mat_mul_T(mat1, mat2);


    // mat_print(mat2);
    // mat_print(mat_d);

    mat_free(&mat1);
    mat_free(&mat2);
    mat_free(&mat_c);
    mat_free(&mat_d);

    printf("\n exiting \n");
    return 0;

}