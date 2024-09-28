#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @namespace activation
 * @brief Contains functions for common activation functions used in neural
 * networks.
 */
namespace activation
{
/**
 * @brief Applies the Rectified Linear Unit (ReLU) activation function
 * element-wise to a matrix.
 *
 * @param mat The input matrix.
 * @return A new matrix with the ReLU activation function applied to
 * each element.
 */
Matrix relu(const Matrix& mat);

/**
 * @brief Applies the softmax activation function element-wise to a matrix.
 *
 * @param mat The input matrix.
 * @return A new matrix with the softmax activation function applied to each
 * element.
 */
Matrix softmax(const Matrix& mat);
}

#endif //ACTIVATION_H