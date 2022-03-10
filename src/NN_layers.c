#include <stdlib.h>
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
    dense_layer->bias = mat_make(1, num_neurons);
    dense_layer->Y = mat_make(1, num_neurons);
    dense_layer->Z = mat_make(1, num_neurons);

    return dense_layer;
}

int dense_set_rand(Dense_layer* dense_layer){
    mat_rand(dense_layer->weights, 0.1); /// sets weights to random values between 0 and 0.1
    mat_zeros(dense_layer->bias); /// sets bias of layer to 0.
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

    return 0;
}