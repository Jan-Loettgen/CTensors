#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H
#include "tensor_2d.h"

typedef struct Dense_layer{
    int num_neurons;
    int num_inputs;
    tensor_2d* weights;
    tensor_2d* bias;
    tensor_2d* Y;
    tensor_2d* Z;
    int (*activation_ptr)(tensor_2d* mat, tensor_2d* mat_out);

}Dense_layer;

int dense_init(unsigned int num_neurons, unsigned int num_inputs, char activation[]);

int dense_init_random();

int dense_set();

int dense_forward(Dense_layer* Dense_layer, tensor_2d* mat_in, tensor_2d* mat_out);

#endif