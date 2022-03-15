#include <stdlib.h>
#include <stdio.h>

#include <cuda.h>

#define NUM_THREADS_PER_BLOCK 256.0


__global__
void vecAddKernal(float *A, float *B, float *C, int n){
    //global thread id used for indexing.
    int i = blockDim.x*blockIdx.x + threadIdx.x;

    //ensure that thread is not trying to access memory outside of arrays.
    if (i<n){
        C[i] = A[i] + B[i];
    }
}

__host__
int array_add_C(float *h_A, float *h_B, float *h_C, int num_elems, int size){
    //allocate device memory for arrays A, B, and C.
    float *d_A, *d_B, *d_C;
    cudaError_t err1 = cudaMalloc((void**) &d_A, size);
    if (err1 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err1),__FILE__,__LINE__);
        return 11;
    }

    cudaError_t err2 = cudaMalloc((void**) &d_B, size);
    if (err2 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err2),__FILE__,__LINE__);
        return 11;
    }

    cudaError_t err3 = cudaMalloc((void**) &d_C, size);
    if (err3 != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err3),__FILE__,__LINE__);
        return 11;
    }

    //copy contents of bariables h_A, and h_B to d_A, and d_B
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    //kernal invocation
    vecAddKernal<<<ceil(num_elems/NUM_THREADS_PER_BLOCK), NUM_THREADS_PER_BLOCK>>>(d_A, d_B, d_C, num_elems);

    //copy device memory to host memory
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    //free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;

}


int main(){
    int num_elems = 24;
    unsigned int size = num_elems*sizeof(float);

    //allocate host memory for arrays A, B, and C.
    float *h_A, *h_B, *h_C;
    h_A = (float*)malloc(size);
    h_B = (float*)malloc(size);
    h_C = (float*)malloc(size);

    ///set arrays to contain random values.
    for (int i = 0; i< 10; i++){
        h_A[i] = rand()/2147483647.0;
    }

    for (int i = 0; i< 10; i++){
        h_B[i] = rand()/2147483647.0;
    }

    for (int i = 0; i< 10; i++){
        h_C[i] = rand()/2147483647.0;
    }


    array_add_C(h_A, h_B, h_C, num_elems, size);


    //do stuff with final array
    for (int i = 0; i< 10; i++){
        printf("%f ", h_A[i]);
    }
    printf("\n");
    for (int i = 0; i< 10; i++){
        printf("%f ", h_B[i]);
    }
    printf("\n");
    for (int i = 0; i< 10; i++){
        printf("%f ", h_C[i]);
    }
    printf("\n");

    //free host memory
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}