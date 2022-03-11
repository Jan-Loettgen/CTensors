/**
 * @file NN_layers.h
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @brief This file contains the declaration of functions and structs of various neural network layer types.
 * @version 0.1
 * @date 10-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H
#include "tensor_2d.h" //! this library is necessary as it provides the backend matrix functionality required for a neural network.

/**
 * @brief This struct defines a Dense layer.
 * 
 * A dense layer is a neural network layer where all neurons are connected to all neurons in the previous layer.
 */
typedef struct Dense_layer{
    int num_neurons; //! Number of neurons in this dense layer
    int num_inputs; //! number of inputs, required to create weights of this layer to inputs.
    tensor_2d* weights; //! A matrix containing the weights of the neurons of this layer to the inuts.
    tensor_2d* bias; //! The bias of each neuron that are added to the weighted sum of inputs.
    tensor_2d* Y; //! This matrix stores the output of the layer before the activation function is applied.
    tensor_2d* Z; //! this matrix stores the final output of the layer, so Y after activation function is applied.
    int (*activation_ptr)(tensor_2d* mat, tensor_2d* mat_out); //! a function pointer to the activation function applied to Y.

}Dense_layer;

/**
 * @brief Function returns a dense layer struct instance, this function is used to initalise a dense layer.
 * 
 * @param[in] num_neurons unsigned int : Number of neurons in this dense layer
 * @param[in] num_inputs unsigned int : number of inputs, required to create weights of this layer to inputs.
 * @param[in] activation function pointer int*(func_ptr)*(mat_in, mat_out), a pointer to the activation function.
 * @return Dense_layer* A struct defining the dense layer
 */
Dense_layer* dense_make(unsigned int num_neurons, unsigned int num_inputs, char activation[]);

/**
 * @brief This function is used to free the memory allocated for a dense layer.
 * 
 * This function is the counter part to the function 'dense_make'.
 * 
 * @param[in] dense_layer A pointer to a pointer to a dense layer that is to be freed.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL.
 */
int dense_free(Dense_layer** dense_layer);

/**
 * @brief This functions sets the weights of the input dense layer to random values in the range [0, scale], biases are set to 0.
 * 
 * @param[in] dense_layer 
 * @param[out] scale
 * @return int 
 */
int dense_set_rand(Dense_layer* Ddnse_layer, int scale);

/**
 * @brief 
 * 
 * @param Dense_layer 
 * @return int 
 */
int dense_set(Dense_layer* dense_layer);

/**
 * @brief 
 * 
 * @param Dense_layer 
 * @param mat_in 
 * @param mat_out 
 * @return int 
 */
int dense_forward(Dense_layer* dense_layer, tensor_2d* mat_in, tensor_2d* mat_out);

#endif