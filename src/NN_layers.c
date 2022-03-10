#include <stdlib.h>
#include <string.h>

#include "tensor_2d.h"
#include "NN_layers.h"
#include "NN_activations.h"

int dense_init(unsigned int num_neurons, unsigned int num_inputs, char activation[]){
    
    Dense_layer* dense_layer = malloc(sizeof(Dense_layer));

    dense_layer->num_neurons = num_neurons;
    dense_layer->num_inputs = num_inputs;

    dense_layer->weights = mat_make(num_inputs, num_neurons);
    dense_layer->bias = mat_make(1, num_neurons);
    dense_layer->Y = mat_make(1, num_neurons);
    dense_layer->Z = mat_make(1, num_neurons);

    if (strcmp(activation, "relu") == 0){
        dense_layer->activation_ptr = &relu;
    }
    else if (strcmp(activation, "linear") == 0){
        dense_layer->activation_ptr = &linear;
    }
    return 0;
}

// int dense_init_random();

// int dense_set();

// int dense_forward(Dense_layer* Dense_layer, tensor_2d* mat_in, tensor_2d* mat_out){



// }