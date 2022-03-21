#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>

extern "C" {

#include "tensor_2d.h"

}

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
    _array_add_kernal<<<ceil(mat_a->n_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_data_A, d_data_B, d_data_out, mat_a->n_elems);

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
    _array_sub_kernal<<<ceil(mat_out->n_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_data_A, d_data_B, d_data_out, mat_a->n_elems);

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
    for (int i = 0; i < 1; i++) {
        cudaGetDeviceProperties(&dev_prop, i);

        printf("dev : %d, clockrate : %d\n", i+1, dev_prop.clockRate);
        printf("dev : %d, concurrentKernels : %d\n", i+1, dev_prop.concurrentKernels  );
        printf("dev : %d, max threads per dim : %d, %d, %d\n", i+1, dev_prop.maxThreadsDim[0],dev_prop.maxThreadsDim[1], dev_prop.maxThreadsDim[2]);
        printf("dev : %d, max Threads Per Block : %d\n", i+1, dev_prop.maxThreadsPerBlock);
        printf("dev : %d, max grid siez per dim : %d, %d, %d\n", i+1, dev_prop.maxGridSize[4],dev_prop.maxGridSize[1], dev_prop.maxGridSize[2]);//futher investigation into the indecies is required.
        printf("dev : %d, warp size : %d\n", i+1, dev_prop.warpSize);
    }
    return 0;
}

__global__
void _mat_mul_kernal(float* data_a, float* data_b, float* data_out, unsigned int mat_a_num_rows, unsigned int mat_a_num_cols, unsigned int mat_b_num_cols){

    unsigned int row = blockDim.y*blockIdx.y + threadIdx.y;
    unsigned int col = blockDim.x*blockIdx.x + threadIdx.x;

    printf("row : %u, col : %u\n", row, col);

    if (row>mat_a_num_rows || col>mat_b_num_cols){
        return;
    }

    float sum = 0;
    unsigned int mat_a_index, mat_b_index;
    for (unsigned int k = 0; k<mat_a_num_cols; k++){
        mat_a_index = row*mat_a_num_cols + k;
        mat_b_index = col + k*mat_b_num_cols;
        sum += data_a[mat_a_index]*data_b[mat_b_index];
    }
    data_out[row + col*mat_b_num_cols] = sum;
}


__host__
int mat_mul_C(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out){
        if (mat_a == NULL || mat_b == NULL || mat_out == NULL){
        return 1;
    }
    if (mat_a->n_cols != mat_b->n_rows){
        return 2;
    }
    if (mat_out->n_rows != mat_a->n_rows || mat_out->n_cols != mat_b->n_cols){
        return 2;
    }

    unsigned int size_a = mat_a->n_elems*sizeof(double);
    unsigned int size_b = mat_b->n_elems*sizeof(double);
    unsigned int size_out = mat_out->n_elems*sizeof(double);

    //allocate device memory for arrays A, B, and output array.
    float *d_data_A, *d_data_B, *d_data_out;
    cudaError_t err1 = cudaMalloc((void**) &d_data_A, size_a);
    if (err1 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err1),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err2 = cudaMalloc((void**) &d_data_B, size_b);
    if (err2 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err2),__FILE__,__LINE__);
        return 101;
    }

    cudaError_t err3 = cudaMalloc((void**) &d_data_out, size_out);
    if (err3 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err3),__FILE__,__LINE__);
        return 101;
    }

    //copy contents of bariables h_A, and h_B to d_A, and d_B
    cudaMemcpy(d_data_A, mat_a->data, size_a, cudaMemcpyHostToDevice);
    cudaMemcpy(d_data_B, mat_b->data, size_b, cudaMemcpyHostToDevice);

    //kernal invocation
    _mat_mul_kernal<<<ceil(mat_a->n_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_data_A, d_data_B, d_data_out, mat_a->n_rows, mat_a->n_cols, mat_b->n_cols);

    //copy device memory to host memory
    cudaMemcpy(mat_out->data, d_data_out, size_out, cudaMemcpyDeviceToHost);

    //free device memory
    cudaFree(d_data_A);
    cudaFree(d_data_B);
    cudaFree(d_data_out);

    return 0;

}

int main(){

    print_device_info();


    tensor_2d* mat_a = mat_make(6, 6);
    tensor_2d* mat_b = mat_make(6, 6);
    tensor_2d* mat_c = mat_make(6, 6);

    mat_rand(0.0, 1.0, mat_a);
    mat_eye(mat_b);

    mat_mul_C(mat_a, mat_b, mat_c);

    mat_print(mat_a);
    mat_print(mat_b);
    mat_print(mat_c);

    // //free host memory
    mat_free(&mat_a);
    mat_free(&mat_b);
    mat_free(&mat_c);
    return 0;
}