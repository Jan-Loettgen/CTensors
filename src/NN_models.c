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

int sequential_free(Sequential** sequential){
    if (*sequential == NULL){
        return 1;
    }
    free(*sequential);
    *sequential= NULL;

    return 0;
}
int sequential_push(Sequential* sequential, void* layer);