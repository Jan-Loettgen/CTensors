/**
 * @file tensor_2d.h
 * @author Jan Loettgen (janlucaloettgen@gmail.com)
 * @brief This file contains the struct definition 'tensor_2d', which acts as a matrix, and function declarations that operate on this struct.
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TENSOR_2D_H
#define TENSOR_2D_H

/**
 * @brief This struct implements a 2 dimensional tensor to represent a matrix.
 */
typedef struct tensor_2d{
    unsigned int n_rows; //! Number of rows in the matrix.
    unsigned int n_cols; //! Number of columns in the matrix.
    unsigned long n_elems; //! Total number of elements stored in matrix
    double* data; //! A pointer to an array of doubles that stores the flattened matrix.

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
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL.
 *
 */
int mat_free(tensor_2d** mat_ptr);

/**
 * @brief Sets all elements of input matrix to zero.
 * 
 * @param[out] mat_out matrix whose values will be set to 0
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL.
 */
int mat_zeros(tensor_2d* mat_out);

/**
 * @brief Sets all elements of input matrix to value in the range of [0, scale].
 * 
 * Note, random number allocate,on is not truly random and should not be used for crytography.
 * Function uses 'rand()' from <stdlib.h> and divivdes by 2147483647.0 to put numbers in the range of [0, 1]
 * 
 * @param[out] mat_out 'tensor_2d' pointer whose values will be set to random numbers.
 * @param[in] scale double: Defines the uper limit of the range of random numbers.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL. 
 */
int mat_rand(tensor_2d* mat_out, double scale);


/**
 * @brief Takes an input matrix and sets its elements to that of an identiy matrix of the same size.
 * 
 * Note the input 'tensor_2d' pointer should point to a square matrix.
 * 
 * @param[out] mat_out 'tensor_2d' pointer with values set to identiy matrix.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrix is not square.  
 */
int mat_eye(tensor_2d* mat_out);


/**
 * @brief Function used to print all the elements of a matrix to the terminal
 * 
 * @param[in] mat A pointer to the matrix to print out.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL
 */
int mat_print(tensor_2d* mat);

/**
 * @brief Function adds input matriceis 'mat_a' and 'mat_b' and stores result in 'mat_out' matrix.
 * 
 * Note 3 input pointers should point to matricies of the same dimensions.
 * 
 * @param[in] mat_a 'tensor_2d' Pointer whose elements should be added to matrix 'mat_b'
 * @param[in] mat_b 'tensor_2d' Pointer whose elements should be added to matrix 'mat_a'
 * @param[out] mat_out 'tensor_2d' Pointer whose elements are the sum of the corresponding elements in matricies 'mat_a' and 'mat_b'
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have different dimensions. 
 */
int mat_add(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out);

/**
 * @brief Function subtracts the elements of matrix 'mat_b' from the corresponding elements of matrix 'mat_a', and stores result in 'mat_out'.
 * 
 * 'mat_out'.data = 'mat_a'.data - 'mat_b'.data
 * 
 * Note 3 input pointers should point to matricies of the same dimensions.
 * 
 * @param[in] mat_a 'tensor_2d' Pointer
 * @param[in] mat_b 'tensor_2d' Pointer
 * @param[out] mat_out 'tensor_2d' Pointer to a matrix that stores the subtraction of elements in 'mat_b' from elements in 'mat_a'.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have different dimensions. 
 */
int mat_subtract(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out);

/**
 * @brief Function multiplies to matricies, and stores result in 'mat_out'.
 * 
 * Note number of columns in 'mat_a' should be equal to number of rows in 'mat_b'.
 * And number of rows of 'mat_out' should be equal to number of rows of 'mat_a',
 * and number of columns of 'mat_out' should be equal to number of columns of 'mat_b',
 * 
 * Performs standard matrix multiplication:
 * 'mat_out'.data = 'mat_a'.data * 'mat_b'.data
 * 
 * @param[in] mat_a 'tensor_2d' Pointer
 * @param[in] mat_b 'tensor_2d' Pointer
 * @param[out] mat_out 'tensor_2d' pointer that stores the results of the matrix multiplication of 'mat_a' and 'mat_b'
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have wrong dimensions. 
 */
int mat_mul(tensor_2d* mat_a, tensor_2d* mat_b, tensor_2d* mat_out);

/**
 * @brief Function tranposes an input matrix and stores the result in the other input matrix.
 * 
 * Note number of rows in 'mat' should be equal to number of columns in 'mat_out',
 * and number of columns in 'mat' should be equal to number of rows in 'mat_out'.
 * 
 * @param[in] mat 'tensor_2d' pointer, to tranpose
 * @param[out] mat_out 'tensor_2d' pointer to store tranposed matrix.
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have wrong dimensions. 
 */
int mat_transpose(tensor_2d* mat, tensor_2d* mat_out);

/**
 * @brief Function used to apply a given input function to all elements of an input matrix, and storing the result in other input matrix.
 *
 * Function iterates over data stored in 'mat' and applies the input function to every element,
 * and stores the result in 'mat_out'
 * Note, both input matricies should have the same dimensions.
 * 
 * @param[in] func Pointer to a function that takes in a double and returns a double.
 * @param[in] mat 'tensor_2d' pointer to whose elements the function should be applied.
 * @param[out] mat_out  'tensor_2d' pointer, which will store the result of applying the function to 'mat'. 
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL, 2 if input matrices have different dimensions. 
 */
int mat_apply_func(double (func)(double d), tensor_2d* mat, tensor_2d* mat_out);

/**
 * @brief Function applies input function to all elements of of the input matrix.
 * 
 * This function is supposed to use to perform analysis on a matrix, and not to modify matrix elements in anyway.
 * 
 * The provided input function should take in a double, a 'reset' flag, and an optional ouput (out_var) variable.
 * The function is applied to all elements in the matrix, and on the last element the reset flag is set to 1.
 * The output varible which the functions takes in, is the same output variable that  this function (mat_apply_func_2),
 * takes as an input. Effectively 'out_var' is the variable that is used in the input function to analyse the matrix.
 * 
 * For example to calculate the sum of the elements of the matrix, the input function should contain a static variable,
 * which is written to the 'out_var' once the reset flag passed in is 1 (e.g on last element in matrix).
 * 
 * Note, this function is entirely different from 'mat_apply_func' as this function does not modify or write,
 * a new matrix, it only applies a function to all elements of a matrix.
 * 
 * The function must take in a double, and should not return anything.
 * 
 * 'out_var' is a void pointer, to allow this function to be used for various purposes, void pointer should be cast,
 * inside 'func'
 * 
 * @param[in] func 
 * @param[in] mat 
 * @param[out] out_var 
 * @return int : 0 if sucessful, 1 : if the dereferenced input pointer points to NULL
 */
int mat_apply_func_2(void (func)(double d, int reset, void* out_var), tensor_2d* mat, void* out_var);

#endif




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