#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tensor_2d.h"
#include "NN_layers.h"
#include "NN_activations.h"

Dense_layer* dense_init(unsigned int num_neurons, unsigned int num_inputs, char activation[]){
    Dense_layer* dense_layer = malloc(sizeof(Dense_layer));

    if (strcmp(activation, "relu") == 0){
        dense_layer->activation_ptr = &relu;
    }
    else if (strcmp(activation, "linear") == 0){
        dense_layer->activation_ptr = &linear;
    }
    else {
        free(dense_layer);
        return NULL;
    }

    dense_layer->num_neurons = num_neurons;
    dense_layer->num_inputs = num_inputs;

    dense_layer->weights = mat_make(num_inputs, num_neurons);
    if (dense_layer->weights == NULL){
        free(dense_layer);
        return NULL;
    }
    dense_layer->bias = mat_make(1, num_neurons);
    if (dense_layer->bias == NULL){
        mat_free(&dense_layer->weights);
        free(dense_layer);
        return NULL;
    }
    dense_layer->Y = mat_make(1, num_neurons);
    if (dense_layer->Y == NULL){
        mat_free(&dense_layer->weights);
        mat_free(&dense_layer->bias);
        free(dense_layer);
        return NULL;
    }
    dense_layer->Z = mat_make(1, num_neurons);
    if (dense_layer->Z == NULL){
        mat_free(&dense_layer->weights);
        mat_free(&dense_layer->bias);
        mat_free(&dense_layer->Z);
        free(dense_layer);
        return NULL;
    }
    return dense_layer;
}

int dense_set_rand(Dense_layer* dense_layer){
    if (dense_layer == NULL){
        return 1;
    }
    mat_rand(dense_layer->weights, 0.1); /// sets weights to random values between 0 and 0.1
    mat_zeros(dense_layer->bias); /// sets bias of layer to 0.

    return 0;
}

// int dense_set();

int dense_forward(Dense_layer* dense_layer, tensor_2d* mat_in, tensor_2d* mat_out){

    int return_code;

    return_code = mat_mul(mat_in, dense_layer->weights, dense_layer->Y); /// X*W = Y
    if (return_code!=0){
        return 3;
    }
    return_code = mat_add(dense_layer->Y, dense_layer->bias, dense_layer->Y);/// Y + B = Y
    if (return_code!=0){
        return 3;
    }
    return_code = dense_layer->activation_ptr(dense_layer->Y, dense_layer->Z);/// f(Y) = Z
    if (return_code!=0){
        return 3;
    }

    mat_copy(dense_layer->Z, mat_out);
    return 0;
}