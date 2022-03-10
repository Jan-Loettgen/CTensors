#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H
#include "tensor_2d.h"



typedef struct Dense_layer{
    int num_neurons;
    int num_neurons_prev;
    tensor_2d* weights;
    tensor_2d* bias;
    tensor_2d* Y;
    tensor_2d Z;
    void* (*function_pointer)(double d);

}Dense_layer;


int dense_init_random();

int dense_set();

int dense_forward(Dense_layer* Dense_layer, tensor_2d* mat_in, tensor_2d* mat_out);

#endif