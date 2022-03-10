/**
 * @file main.c
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @brief 
 * @version 0.1
 * @date 09-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @mainpage CTensors Documentation
 * @section Overview Overview
 * ladida
 * 
 * @section Explaining_packages Included Packages
 * This is an explanation of the various files
 * 
 * @section how_to Instructions
 * testing
 * 
 * @date 09-03-2022
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "tensor_2d.h"
#include "tensor_2d_threaded.h"

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
    
    tensor_2d* mat1 = mat_make(5,5);
    tensor_2d* mat2 = mat_make(5,5);

    tensor_2d* mata = mat_make(5,5);
    tensor_2d* matb = mat_make(5,5);
    
    mat_eye(mat1);
    mat_rand(mat2, 1);

    mat_mul(mat1, mat2, mata);
    mat_add(mat1, mat2, matb);


    // mat_print(mat2);
    mat_print(mata);
    mat_print(matb);

    mat_free(&mat1);
    mat_free(&mat2);
    mat_free(&mata);
    mat_free(&matb);

    printf("\n exiting \n");
    return 0;

}