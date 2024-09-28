//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

/**
 * @class MlpNetwork
 * @brief Represents a Multi-Layer Perceptron (MLP) neural network.
 *
 * The MlpNetwork class represents an MLP neural network consisting of
 * multiple layers.
 */
class MlpNetwork {

 private:
  Dense _layer1; /**< The first dense layer of the MLP network. */
  Dense _layer2; /**< The second dense layer of the MLP network. */
  Dense _layer3; /**< The third dense layer of the MLP network. */
  Dense _layer4; /**< The forth dense layer of the MLP network. */


 public:
/**
 * @brief Constructs an MLP network with the specified weights and biases.
 *
 * @param weights An array of weight matrices for each layer in the MLP
 * network.
 * @param biases An array of bias matrices for each layer in the MLP network.
 */
  MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

/**
 * @brief Computes the output digit classification given an input image.
 *
 * @param img The input image matrix.
 * @return The classified digit output.
 */
  digit operator()(Matrix& img)const;
};

#endif // MLPNETWORK_H

