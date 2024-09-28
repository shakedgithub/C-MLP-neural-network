#include "Dense.h"


Dense::Dense (Matrix& weights, Matrix& bias, Activation_Func
activation_func) : _weights(weights), _bias(bias), _activation_func
(activation_func) {}


Matrix Dense::get_weights ()const
{
  return _weights;
}


Matrix Dense::get_bias ()const
{
  return _bias;
}


Activation_Func Dense::get_activation ()const
{
  return _activation_func;
}


Matrix Dense::operator() (const Matrix& input_vec)const
{
  return Matrix(_activation_func((_weights * input_vec) + _bias));
}










