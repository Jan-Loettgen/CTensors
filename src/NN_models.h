/**
 * @file NN_model.h
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @brief This file defines a Sequential neural network model.
 * @version 0.1
 * @date 11-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NN_MODEL_H
#define NN_MODEL_H

#define MAX_NUM_LAYERS 100 ///< maximmum number of layers that a sequential object can ahve.

#include "NN_layers.h" ///< this dependency is required for management of the layers.

typedef struct Sequential{
    int num_layers; ///< number of layers that this sequential struct has.
    void* layers[MAX_NUM_LAYERS]; ///< A pointer to an array of pointers to layers.
    const char* layer_types[10]; ///< Pointer to an array of pointers to strings, each string should correspond to the type of the corresponding layer.
}Sequential;

Sequential* sequential_make();

int sequential_free(Sequential* sequential);

int sequential_push(Sequential* sequential, void* layer);

#endif