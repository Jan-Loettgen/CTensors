/**
 * @file NN_activations.h
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @brief This file contains the function declarations of activation functions that can be used in layers defined in 'NN_layers.h'.
 * 
 * @version 0.1
 * @date 10-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NN_ACTIVATIONS_H
#define NN_ACTIVATIONS_H
#include "tensor_2d.h" //! this library is necessary as it provides the backend matrix functionality required for a neural network.

/**
 * @brief Rectified linear function, any elements in the 'mat' matrix that are less than 0.0 are set to 0.0 in the mat_out matrix.
 * 
 * @param[in] mat input matrix to whose elements the relu function is applied.
 * @param[out] mat_out The ouput matrix, its elements are the result of applying the relu function to the input matrix 'mat'.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have different dimensions.
 */
int relu(tensor_2d* mat, tensor_2d* mat_out);


/**
 * @brief Linear activation function, which just copies the contents of the 'mat' matrix into the 'mat_out' matrix.
 * 
 * @param[in] mat input matrix whose elements are copied.
 * @param[out] mat_out matrix to which the input matrix 'mat' elements are copied. 
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have different dimensions. 
 */
int linear(tensor_2d* mat, tensor_2d* mat_out);

#endif