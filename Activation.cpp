#include "Activation.h"


Matrix activation::relu (const Matrix &mat)
{
  int rows_num = mat.get_rows();
  int cols_num = mat.get_cols();
  Matrix relu_mat = Matrix(rows_num, cols_num);
  for (int i = 0; i < rows_num; i++)
  {
    for (int j = 0; j < cols_num; j++)
    {
      if (mat(i,j) >= 0)
      {
        relu_mat(i,j) = mat(i,j);
      }
      else
      {
        relu_mat(i,j) = 0;
      }
    }
  }
  return relu_mat;
}

Matrix activation::softmax(const Matrix& mat)
{

  int rows_num = mat.get_rows();
  int cols_num = mat.get_cols();
  Matrix softmax_mat(rows_num, cols_num);
  for (int i = 0; i < rows_num * cols_num ; ++i)
  {
    softmax_mat[i] = std::exp (mat[i]);
  }
  float sum_of_ex = softmax_mat.sum();
  float scalar = 1 / sum_of_ex;

  return scalar * softmax_mat;
}