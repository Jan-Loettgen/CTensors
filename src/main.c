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

    // tensor_2d* mat1 = mat_rand(5, 5);
    // tensor_2d* mat2 = mat_rand(5, 5);

    // tensor_2d* mat_c = mat_subtract_T(mat1, mat2);

    // tensor_2d* mat_d = mat_apply_func(&ReLu, mat_c);

    double* data_source = malloc(25*sizeof(double));

    // for (double i = 0.0; i<25; i++){
    //     data_source[(int)i] = i;
    // }

    double* data1 = malloc(5*sizeof(double));
    //double* data2 = malloc(5*sizeof(double));

    for (int i = 0; i<5; i++){
        data1[i] = (data_source[i*(5)]);
    }

    printf("double : %f", (data1[4]));
    // mat_print(mat_c);
    // mat_print(mat_d);

    // mat_free(&mat1);
    // mat_free(&mat2);
    // mat_free(&mat_c);

    printf("\n exiting \n");
    return 0;

}