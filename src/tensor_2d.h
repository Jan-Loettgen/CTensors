#ifndef TENSOR_2D_H
#define TENSOR_2D_H

typedef struct tensor_2d{
    unsigned int n_rows;
    unsigned int n_cols;
    unsigned long n_elems;
    double* data;

} tensor_2d;


/**
 * @brief Function reutrns a pointer to a matrix, with specfied number of rows and columns.
 * Function uses malloc to allocate memory for a 'tensor_2d' sturct which acts as a 2 
 * dimensional matrix. The actual matrix elemetns are stroed in tensor_2d.data.
 * 
 * Note matrix variables are note initalised to any specfic value!!!
 * Maximum allowed matrix size is specfied by 'MAX_NUM_ELEMENTS' in 'tensor_2d.c' as 268435456.
 * Corresponding to a matrix of 16384 rows and 16384 columns, using 0.25GB of ram, to store.
 * 
 * @param[in] num_rows unsigned int: the number of rows the matrix should have.
 * @param[in] num_cols unsigned int: the number of columns the matrix should have.
 * @return tensor_2d* A pointer to a tensor_2d object that acts as a matrix.
 */
tensor_2d* mat_make(unsigned int num_rows, unsigned int num_cols);


/**
 * @brief Function takes in a pointer to a pointer to a matrix, and frees the memory of 'tensor_2d' struct
 * Function sets the pointer that the input pointer points to NULL after freeing momeory.
 * This function is effectivelz the counter part to 'mat_make'
 * 
 * @param[in] mat_ptr A pointer to a pointer where the 'tensor_2d' sturct is located.
 */
void mat_free(tensor_2d** mat_ptr);

/**
 * @brief Function returns a pointer to a matrix of specfied number of rows and columns whose elements are zero.
 * 
 * @param[in] num_rows unsigned int: the number of rows the matrix should have.
 * @param[in] num_cols unsigned int: the number of columns the matrix should have.
 * @return tensor_2d* A pointer to a tensor_2d object that acts as a matrix.
 */
tensor_2d* mat_zeros(unsigned int num_rows, unsigned int num_cols);

/**
 * @brief Function returns a pointer to matrix of specfied number of rows and columns whose elements are random numbers.
 * Random numbers are in the range of [0, 1].
 * Note, random number allocate,on is not truly random and should not be used for crytography.
 * Function uses 'rand()' from <stdlib.h> and divivdes by 2147483647.0 to put numbers in the range of [0, 1]
 * 
 * 
 * @param[in] num_rows unsigned int: the number of rows the matrix should have.
 * @param[in] num_cols unsigned int: the number of columns the matrix should have.
 * @return tensor_2d* A pointer to a tensor_2d object that acts as a matrix.
 */
tensor_2d* mat_rand(unsigned int num_rows, unsigned int num_cols);


/**
 * @brief Function reutrns a pointer to a square identity matrix with number of rows and columns specfied.
 * 
 * @param[in] num_rows  unsigned int: number of rows, and also of columns of the square identiy matrix
 * @return tensor_2d* A pointer to a tensor_2d object that acts as a matrix. 
 */
tensor_2d* mat_eye(unsigned int num_rows);


/**
 * @brief Function used to print all the elements of a matrix to the terminal
 * 
 * @param[in] mat A pointer to the matrix to print out.
 */
void mat_print(tensor_2d* mat);

/**
 * @brief Function adds two input matricies and reutrns a new matrix,.
 * Function adds two input matricies, of the same shape,
 * and returns a new matrix of the same shape as the input matricies.
 * 
 * Note function returns NULL if input matricis are NULL or of different dimensions.
 * 
 * @param[in] mat_a A pointer to matrix a in same shape as matrix b
 * @param[in] mat_b A pointer to matrix b in same shape as matrix a
 * @return tensor_2d* A pointer to a matrix, whos elements are the sum of
 * the corresponding elements in matricies a and b.
 */
tensor_2d* mat_add(tensor_2d* mat_a, tensor_2d* mat_b);

/**
 * @brief Function subtracts second input matrix from first and reutrns a new matrix.
 * Function subtracts matrix 'mat_b' from matrix 'mat_a'
 * and returns a new matrix of the same shape as the input matricies.
 * 
 * Note function returns NULL if input matricis are NULL or of different dimensions.
 * 
 * @param[in] mat_a A pointer to a matrix from which matrix 'mat_b' should be subtracted
 * @param[in] mat_b A pointer to the matrix which should be subtracted from matrix 'mat_a'.
 * @return tensor_2d* Pointer to a new matrix, whos elements are the corrspoding
 * elements in matrix 'mat_a' a minus the corresponding elements in matrix 'mat_b'.
 */
tensor_2d* mat_subtract(tensor_2d* mat_a, tensor_2d* mat_b);

/**
 * @brief Function that performs threaded matrix calculation of the input matricies, and reutrns a new matrix.
 * Performs standard matrix multiplication in the order 'mat_a' * 'mat_b'.
 * 
 * Note function returns NULL if number of columns in matrix 'mat_a' is not equal to
 * Number of rows in matrix 'mat_b', or if either input matrix is a NULL pointer.
 * 
 * @param[in] mat_a A pointer to a matrix 
 * @param[in] mat_b A pointer to a different matrix
 * @return tensor_2d* A pointer to a new matrix, whose elements are the results of the matrix
 * multiplication 'mat_a' * 'mat_b'
 */
tensor_2d* mat_mul(tensor_2d* mat_a, tensor_2d* mat_b);

/**
 * @brief Function returns a pointer to a new matrix that is the tranpose of the input matrix.
 * 
 * i.e. new matrix has the same number of rows as the input matrix has columns, 
 * and same number of columns as input matrix has rows.
 * Elements are the tranpose of the input matrix.
 * 
 * @param[in] mat A pointer to a new matrix that whose elements are trnapose relative to input matrix.
 * @return tensor_2d* A pointer to a matrix
 */
tensor_2d* mat_transpose(tensor_2d* mat);

/**
 * @brief A function used to apply an input function to every element of the input matrix.
 * 
 * Note, input function is applied to all elements individually.
 * 
 * @param[in] func A pointer to a function that takes in a double and returns a double.
 * @param[in] mat A pointer matrix to whose elements the function should be applied
 * @return tensor_2d* A pointer to a new matrix whose elements have had the function applied to them.
 */
tensor_2d* mat_apply_func(double (func)(double d), tensor_2d* mat);

/**
 * @brief Applies input function to all elements, and then returns what the function returns on the last element.
 * 
 * Note this function is different from function 'mat_apply_func' because that function returns
 * a matrix that has had the function applied to it. This function instead applies the input function
 * to all elements and returns the function return, on the final element. This method could be used to
 * calculate the sum of all elements of a matrix by using static variables in the input function.
 * 
 * To accomadate static variables the function should take as input a reset value.
 * This will be 1 on the last element of the matrix, and will be 0 otherwise.
 * 
 * 
 * @param[in] func A pointer to a Function that accepts a double, and a reset flag.
 * @param[in] mat  A pointer to a matrix to whose elements the function should be applied.
 * @return returns whatever the function returns after being called on final elememnt.
 */
void* mat_apply_func_2(void* (func)(double d, int reset, void* out_var), tensor_2d* mat, void* out_var);

#endif