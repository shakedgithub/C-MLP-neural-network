#include "MlpNetwork.h"


MlpNetwork::MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
    :
      _layer1(weights[0], biases[0], activation::relu),
      _layer2(weights[1], biases[1], activation::relu),
      _layer3(weights[2], biases[2], activation::relu),
      _layer4(weights[3], biases[3], activation::softmax)
{}


digit MlpNetwork::operator() (Matrix& vec) const
{
  vec = vec.vectorize();
  Matrix r1 = _layer1(vec);
  Matrix r2 = _layer2(r1);
  Matrix r3 = _layer3(r2);
  Matrix r4 = _layer4(r3);
  unsigned int max_ind = r4.argmax();
  float prob = r4[(int)max_ind];
  digit result{max_ind, prob};
  return result;
}