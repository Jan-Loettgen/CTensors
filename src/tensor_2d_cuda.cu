#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>

#include "tensor_2d.h"

#define NUM_THREADS_PER_BLOCK 256.0


__global__
void _array_add_kernal(float *A, float *B, float *C, int n){
    //global thread id used for indexing.
    int i = blockDim.x*blockIdx.x + threadIdx.x;

    //ensure that thread is not trying to access memory outside of arrays.
    if (i<n){
        C[i] = A[i] + B[i];
    }
}

__host__
int mat_add_C(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL|| mat_out == NULL){
        return 1;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_cols != mat_out->n_cols){
        return 2;
    }
    else if (mat_a->n_rows != mat_b->n_rows || mat_a->n_rows != mat_out->n_rows){
        return 2;
    }

    unsigned int size = mat_a->n_elems*sizeof(double);

    //allocate device memory for arrays A, B, and output array.
    float *d_data_A, *d_data_B, *d_data_out;
    cudaError_t err1 = cudaMalloc((void**) &d_data_A, size);
    if (err1 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err1),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err2 = cudaMalloc((void**) &d_data_B, size);
    if (err2 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err2),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err3 = cudaMalloc((void**) &d_data_out, size);
    if (err3 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err3),__FILE__,__LINE__);
        return 101;
    }

    //copy contents of bariables h_A, and h_B to d_A, and d_B
    cudaMemcpy(d_data_A, mat_a->data, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_data_B, mat_b->data, size, cudaMemcpyHostToDevice);

    //kernal invocation
    _arrayAddKernal<<<ceil(mat_a->n_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_data_A, d_data_B, d_data_out, mat_a->n_elems);

    //copy device memory to host memory
    cudaMemcpy(mat_out->data, d_data_out, size, cudaMemcpyDeviceToHost);

    //free device memory
    cudaFree(d_data_A);
    cudaFree(d_data_B);
    cudaFree(d_data_out);

    return 0;
}

__global__
void _array_sub_kernal(float *A, float *B, float *C, int n){
    //global thread id used for indexing.
    int i = blockDim.x*blockIdx.x + threadIdx.x;

    //ensure that thread is not trying to access memory outside of arrays.
    if (i<n){
        C[i] = A[i] - B[i];
    }
}

__host__
int mat_sub_C(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
    if (mat_a == NULL || mat_b == NULL|| mat_out == NULL){
        return 1;
    }
    else if (mat_a->n_cols != mat_b->n_cols || mat_a->n_cols != mat_out->n_cols){
        return 2;
    }
    else if (mat_a->n_rows != mat_b->n_rows || mat_a->n_rows != mat_out->n_rows){
        return 2;
    }

    unsigned int size = mat_a->n_elems*sizeof(double);

    //allocate device memory for arrays A, B, and output array.
    float *d_data_A, *d_data_B, *d_data_out;
    cudaError_t err1 = cudaMalloc((void**) &d_data_A, size);
    if (err1 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err1),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err2 = cudaMalloc((void**) &d_data_B, size);
    if (err2 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err2),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err3 = cudaMalloc((void**) &d_data_out, size);
    if (err3 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err3),__FILE__,__LINE__);
        return 101;
    }

    //copy contents of bariables h_A, and h_B to d_A, and d_B
    cudaMemcpy(d_data_A, mat_a->data, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_data_B, mat_b->data, size, cudaMemcpyHostToDevice);

    //kernal invocation
    _array_sub_kernal<<<ceil(mat_a->n_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_data_A, d_data_B, d_data_out, mat_a->n_elems);

    //copy device memory to host memory
    cudaMemcpy(mat_out->data, d_data_out, size, cudaMemcpyDeviceToHost);

    //free device memory
    cudaFree(d_data_A);
    cudaFree(d_data_B);
    cudaFree(d_data_out);

    return 0;
}
__host__
int print_device_info(){
    cudaDeviceProp dev_prop;
    for (int i = 0; i < dev_count; i++) {
        cudaGetDeviceProperties(&dev_prop, i);

        printf("dev : %d, clockrate : %d\n", i+1, dev_prop.clockRate);
        printf("dev : %d, concurrentKernels : %d\n", i+1, dev_prop.concurrentKernels  );
        printf("dev : %d, max threads per dim : %d, %d, %d\n", i+1, dev_prop.maxThreadsDim[0],dev_prop.maxThreadsDim[1], dev_prop.maxThreadsDim[2]);
        printf("dev : %d, max Threads Per Block : %d\n", i+1, dev_prop.maxThreadsPerBlock);
        printf("dev : %d, max grid siez per dim : %d, %d, %d\n", i+1, dev_prop.maxGridSize[0],dev_prop.maxGridSize[1], dev_prop.maxGridSize[2]);
        printf("dev : %d, warp size : %d\n", i+1, dev_prop.warpSize);
    }
    return 0;
}


int main(){




    tensor_2d* mat_a = mat_make(24, 24);
    tensor_2d* mat_b = mat_make(24, 24);
    tensor_2d* mat_c = mat_make(24, 24);

    mat_rand(0.0, 1.0, mat_a);
    mat_zeros(mat_b);

    mat_add_C(mat_a, mat_b, mat_c);

    mat_print(mat_a);
    mat_print(mat_b);
    mat_print(mat_c);

    //free host memory
    mat_free(&mat_a);
    mat_free(&mat_b);
    mat_free(&mat_c);
    return 0;
}