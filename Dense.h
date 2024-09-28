#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**   typedefs  */
typedef Matrix (*Activation_Func)(const Matrix&);

/**
 * @class Dense
 * @brief Represents a dense layer in a neural network.
 *
 * The Dense class encapsulates the weights, bias, and activation function
 * of a dense layer in a neural network.
 */
class Dense{

 private:
  Matrix _weights; /**< The weight matrix of the dense layer. */
  Matrix _bias; /**< The bias matrix of the dense layer. */
  Activation_Func _activation_func; /**< The activation function of the
 * dense layer. */


 public:

/**
 * @brief Constructs a Dense layer with the specified weights, bias, and
 * activation function.
 *
 * @param weights The weight matrix of the dense layer.
 * @param bias The bias matrix of the dense layer.
 * @param activation_func The activation function of the dense layer.
 */
  Dense(Matrix& weights, Matrix& bias, Activation_Func activation_func);

/**
 * @brief Returns the weight matrix of the dense layer.
 *
 * @return The weight matrix.
 */
  Matrix get_weights()const;

/**
 * @brief Returns the bias matrix of the dense layer.
 *
 * @return The bias matrix.
 */
  Matrix get_bias()const;

/**
 * @brief Returns the activation function of the dense layer.
 *
 * @return The activation function.
 */
  Activation_Func get_activation()const;

/**
 * @brief Computes the output of the dense layer given an input vector.
 *
 * @param input_vec The input vector to the dense layer.
 * @return The output matrix computed by applying the weights, bias, and
 * activation function.
 */
  Matrix operator()(const Matrix& input_vec)const;
};


#endif //DENSE_H
