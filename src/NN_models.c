/**
 * @file NN_models.c
 * @author Jan Luca Loettgen (janlucaloettgen@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "NN_models.h"
#include <stdlib.h>

Sequential* sequential_make(){
    Sequential* sequential = malloc(sizeof(Sequential));

    if (sequential == NULL){
        return NULL;
    }
    else{
        return sequential;
    }
}

int sequential_free(Sequential** sequential_ptr){
    if (*sequential_ptr == NULL){
        return 1;
    }

    for (int i=0; i<(*sequential_ptr)->num_layers; i++) {

        if ((*sequential_ptr)->layer_types == "dense"){
            dense_free((*sequential_ptr)->layers[i]);
        }
        else {
            return 4;///< return code means that there was a layer of unknown type
        }
    }

    free(*sequential_ptr);
    *sequential_ptr= NULL;

    return 0;
}
int sequential_push(Sequential* sequential, void* layer);