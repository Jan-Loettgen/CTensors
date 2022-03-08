#ifndef TENSOR_2D_THREADED_H
#define TENSOR_2D_THREADED_H

/**
 * @brief Function adds two input matricies and reutrns a new matrix, addition is multithreaded.
 * Function adds two input matricies, of the same shape,
 * and returns a new matrix of the same shape as the input matricies.
 * The addition is multithreaded using pthreads, which may decrease
 * computation time for large matricies relative to unthreaded 'mat_add' function.
 * 
 * Note function returns NULL if input matricis are NULL or of different dimensions.
 * 
 * @param[in] mat_a A pointer to matrix a in same shape as matrix b
 * @param[in] mat_b A pointer to matrix b in same shape as matrix a
 * @return tensor_2d* A pointer to a matrix, whos elements are the sum of
 * the corresponding elements in matricies a and b.
 */
tensor_2d* mat_add_T(tensor_2d* mat_a, tensor_2d* mat_b);

/**
 * @brief Function subtracts second input matrix from first and reutrns a new matrix, subtraction is multithreaded.
 * Function subtracts matrix 'mat_b' from matrix 'mat_a'
 * and returns a new matrix of the same shape as the input matricies.
 * The subtraction is multithreaded using pthreads, which may decrease
 * computation time for large matricies relative to unthreaded 'mat_subtract' function.
 * 
 * Note function returns NULL if input matricis are NULL or of different dimensions.
 * 
 * @param mat_a A pointer to a matrix from which matrix 'mat_b' should be subtracted
 * @param mat_b A pointer to the matrix which should be subtracted from matrix 'mat_a'.
 * @return tensor_2d* Pointer to a new matrix, whos elements are the corrspoding
 * elements in matrix 'mat_a' a minus the corresponding elements in matrix 'mat_b'.
 */
tensor_2d* mat_subtract_T(tensor_2d* mat_a, tensor_2d* mat_b);

/**
 * @brief Function that performs threaded matrix calculation of the input matricies, and reutrns a new matrix.
 * Performs standard matrix multiplication in the order 'mat_a' * 'mat_b'.
 * The multiplication is row threaded for matrix 'mat_a', meaning each thread computes
 * one of the rows of the output matrix. This may decrease computation time,
 * for matricies with a large number of rows, relative to the function 'mat_mul'
 * 
 * Note function returns NULL if number of columns in matrix 'mat_a' is not equal to
 * Number of rows in matrix 'mat_b', or if either input matrix is a NULL pointer.
 * 
 * @param mat_a A pointer to matrix 
 * @param mat_b A pointer to a matrix
 * @return tensor_2d* A pointer to a new matrix, whose elements are the results of the matrix
 * multiplication 'mat_a' * 'mat_b'
 */
tensor_2d* mat_mul_T(tensor_2d* mat_a, tensor_2d* mat_b);   
#endif