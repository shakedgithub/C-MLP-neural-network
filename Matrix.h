// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>
#include <stdexcept>

using std::ostream;
using std::istream;
using std::cout;
using std::cin;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;


/**
* @class Matrix
* @brief Represents a mathematical matrix.
*
* This class provides operations and functionality for working with matrices.
*/
class Matrix {

 private:
//  int mat_rows; /**< The number of rows in the matrix. */
//  int mat_cols; /**< The number of cols in the matrix. */
  matrix_dims mat_dims; /**< The dimensions of the matrix. */
  float *mat_data; /**< The one-dimensional array representing the matrix
 * data. */


 public:
/**
* @brief Constructs a matrix with the specified number of rows and columns.
*
* @param rows The number of rows in the matrix.
* @param cols The number of columns in the matrix.
*/
  Matrix(int rows, int cols);

/**
* @brief Default constructor. Constructs an empty matrix with zero rows and
* zero columns.
*/
  Matrix();

/**
* @brief Copy constructor. Constructs a matrix by copying the contents of
 * another matrix.
*
* @param other_mat The matrix to be copied.
*/
  Matrix(const Matrix& other_mat);

/**
* @brief Destructor. Frees the dynamically allocated memory used by the
* matrix.
*/
  ~Matrix();

/**
* @brief Returns the number of rows in the matrix.
*
* @return The number of rows.
*/
  int get_rows() const;

/**
* @brief Returns the number of columns in the matrix.
*
* @return The number of columns.
*/
  int get_cols() const;

  // operators:

/**
* @brief Adds another matrix to the current matrix and returns the result.
*
* @param other_mat The matrix to be added.
* @return A new matrix that is the result of adding the current matrix with
* the other matrix.
*/
  Matrix operator+(const Matrix& other_mat) const;

/**
* @brief Assigns the values of another matrix to the current matrix.
*
* @param other_mat The matrix whose values will be assigned.
* @return A reference to the current matrix after the assignment.
*/
  Matrix& operator=(const Matrix& other_mat);

/**
* @brief Adds the values of another matrix to the current matrix.
*
* @param other_mat The matrix to be added.
* @return A reference to the current matrix after the addition.
*/
  Matrix& operator+=(const Matrix& other_mat);

/**
* @brief Accesses the element at the specified row and column using
* parentheses notation.
*
* @param i The row index.
* @param j The column index.
* @return A reference to the element at the specified position.
*/
  float& operator()( int i,  int j);

/**
* @brief Accesses the element at the specified row and column using
* parentheses notation (const version).
*
* @param i The row index.
* @param j The column index.
* @return A const reference to the element at the specified position.
*/
  const float& operator()(int i, int j) const;

/**
* @brief Accesses the element at the specified index using square bracket
* notation/
*
* @param i The index.
* @return A reference to the element at the specified index.
*/
  float& operator[](int i);

/**
* @brief Accesses the element at the specified index using square bracket
* notation (const version).
*
* @param i The index.
* @return A const reference to the element at the specified index.
*/
  const float& operator[](int i) const;

/**
* @brief Multiplies the matrix by a scalar value and returns the result.
*
* @param c The scalar value to multiply the matrix by.
* @return A new matrix that is the result of multiplying the current matrix
* by the scalar value/
*/
  Matrix operator* (float c);

  // functions:

/**
* @brief Transposes the matrix in-place.
*
* @return A reference to the transposed matrix.
*/
  Matrix& transpose();

/**
* @brief Vectorizes the matrix, converting it into a column vector.
*
* @return A reference to the vectorized matrix.
*/
  Matrix& vectorize();

/**
* @brief Prints the matrix in a plain format.
*
* @return No return value for this function.
*/
  void plain_print() const;

/**
* @brief Computes the dot product between the current matrix and another
* matrix.
*
* @param other_mat The matrix to compute the dot product with.
* @return A new matrix that is the result of the dot product.
*/
  Matrix dot(const Matrix& other_mat) const;

/**
* @brief Computes the norm (magnitude) of the matrix.
*
* @return The norm of the matrix as a floating-point value.
*/
  float norm()const;

/**
* @brief Computes the reduced row-echelon form (rref) of the matrix.
*
* @return The reduced row-echelon form of the matrix as a new matrix.
*/
  Matrix rref()const; // need to complete

/**
* @brief Returns the index of the maximum element in the matrix.
*
* @return The index of the maximum element.
*/
  int argmax()const;

/**
* @brief Computes the sum of all elements in the matrix.
*
* @return The sum of all elements as a floating-point value.
*/
  float sum()const;

  // friends:

/**
* @brief Multiplies two matrices and returns the result.
*
* @param r_mat The right-hand side matrix.
* @param l_mat The left-hand side matrix.
* @return A new matrix that is the result of the multiplication.
*/
  friend Matrix operator* (const Matrix &r_mat, const Matrix &l_mat);

/**
* @brief Multiplies a scalar value by a matrix and returns the result.
*
* @param c The scalar value to multiply by.
* @param mat The matrix to multiply.
* @return A new matrix that is the result of the multiplication.
*/
  friend Matrix operator* (float c, const Matrix& mat);

/**
* @brief Inserts the matrix into the output stream.
*
* @param s The output stream.
* @param mat The matrix to be inserted.
* @return A reference to the output stream after insertion.
*/
  friend ostream& operator<< (ostream& s ,const Matrix& mat);

/**
* @brief Extracts the matrix from the input stream.
*
* @param s The input stream.
* @param mat The matrix to be extracted.
* @return A reference to the input stream after extraction.
*/
  friend istream& operator>> (istream& s, Matrix& mat);

};


#endif //MATRIX_H