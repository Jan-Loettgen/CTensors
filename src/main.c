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
#include "NN_layers.h"

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
    
    Dense_layer dense_layer = dense_init(4, 10, "relu");
    dense_set_rand(dense_layer);

    dense_forward();


    printf("\n exiting \n");
    return 0;

}