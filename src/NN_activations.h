#ifndef NN_ACTIVATIONS_H
#define NN_ACTIVATIONS_H
#include "tensor_2d.h"

int relu(tensor_2d* mat, tensor_2d* mat_out);

int linear(tensor_2d* mat, tensor_2d* mat_out);

#endif