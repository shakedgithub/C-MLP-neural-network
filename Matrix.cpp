#include "Matrix.h"


#define ONE 1
#define BIG_ENOUGH 0.1
#define VERY_SMALL_NUMBER 1e-3
#define PIVOT_ROW_NOT_FOUND (-1)


#define SIZE_ERROR "Error: Matrix sizes are incompatible for the operation"
#define OUT_OF_RANGE_ERROR "Error: Index out of range"
#define STREAM_ERROR "Error: Insufficient data for matrix elements."

// Helper function declarations
/**
 * @brief Finds the pivot row for Gaussian elimination.
 *
 * This function searches for a non-zero entry in the lead column of the
 * reduced row-echelon form (RREF) matrix,
 * starting from the current row index, and returns the row index of the
 * pivot row.
 * If no non-zero entry is found, it returns -1.
 *
 * @param rref_mat The RREF matrix.
 * @param current_row The current row index.
 * @param lead The lead column index.
 * @return The row index of the pivot row, or -1 if not found.
 */
int find_pivot_row(const Matrix& rref_mat, int current_row, int lead);

/**
 * @brief Swaps two rows in the matrix.
 *
 * This function swaps the positions of two rows in the matrix.
 *
 * @param rref_mat The matrix in which rows will be swapped.
 * @param row1 The index of the first row.
 * @param row2 The index of the second row.
 */
void swap_rows(Matrix& rref_mat, int row1, int row2);

/**
 * @brief Divides a row in the matrix by a divisor.
 *
 * This function divides all elements of a row in the matrix by a given
 * divisor.
 *
 * @param rref_mat The matrix in which the row will be divided.
 * @param row The index of the row to be divided.
 * @param divisor The value by which the row will be divided.
 */
void divide_row(Matrix& rref_mat, int row, float divisor);

/**
 * @brief Eliminates rows below and above the pivot row.
 *
 * This function performs row elimination to create zeros in the lead column
 * of rows below and above the pivot row in the matrix.
 *
 * @param rref_mat The matrix in which rows will be eliminated.
 * @param pivot_row The index of the pivot row.
 * @param lead The lead column index.
 */
void eliminate_rows(Matrix& rref_mat, int pivot_row, int lead);

/**
 * @brief Rounds small values in the matrix to zero.
 *
 * This function iterates through all elements of the matrix and rounds values
 * that are smaller than a predefined threshold to zero.
 *
 * @param rref_mat The matrix in which small values will be rounded to zero.
 */
void round_small_values(Matrix& rref_mat);


Matrix::Matrix (int rows, int cols) : mat_dims {rows,cols} //CONSTRUCTOR
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error(SIZE_ERROR);
  }
  mat_data = new float[rows * cols](); // () is for initialize to zero
}


Matrix::Matrix (): Matrix (1,1) {}


Matrix::Matrix(const Matrix& other_mat) :
mat_dims ({other_mat.mat_dims.rows, other_mat.mat_dims.cols})
// COPY CONSTRUCTOR
{
  mat_data = new float [mat_dims.rows * mat_dims.cols]();
  for (int i = 0; i < mat_dims.rows * mat_dims.cols; ++i) // deep copy
  {
    mat_data[i] = other_mat.mat_data[i];
  }
}


Matrix::~Matrix () // DESTRUCTOR
{
  delete[] mat_data;
  mat_data = nullptr;
}


int Matrix::get_rows ()const {return mat_dims.rows;}


int Matrix::get_cols ()const {return mat_dims.cols;}


Matrix& Matrix::transpose()
{
  Matrix old_mat = (*this); // copy constructor
  for (int i = 0; i < mat_dims.cols; ++i)
  {
    for (int j = 0; j < mat_dims.rows; ++j)
    {
      mat_data[i * mat_dims.rows + j] =
          old_mat.mat_data[ j * mat_dims.cols + i];
    }
  }
  mat_dims = {old_mat.mat_dims.cols, old_mat.mat_dims.rows};
  return *this;
}


Matrix& Matrix::vectorize ()
{
  mat_dims = {mat_dims.rows * mat_dims.cols, ONE};
  return *this;
}


void Matrix::plain_print () const
{
  for (int i = 0; i < mat_dims.rows; ++i)
  {
    for (int j = 0; j < mat_dims.cols; ++j)
    {
      std::cout << mat_data[i * mat_dims.cols + j] << " ";
    }
    std::cout << "\n";
  }
}


Matrix Matrix::dot (const Matrix &other_mat) const
{
  // check if the other matrix in the same sizes of "this"
  if (mat_dims.rows != other_mat.mat_dims.rows ||
  mat_dims.cols != other_mat.mat_dims.cols)
  {
    throw std::length_error (SIZE_ERROR);
  }
  Matrix dot_mat(mat_dims.rows, mat_dims.cols);
  for (int i = 0; i < mat_dims.cols * mat_dims.rows; i++)
  {
    dot_mat.mat_data[i] = (this->mat_data[i] * other_mat.mat_data[i]);
  }
  return dot_mat;
}


float Matrix::norm () const
{
  float sum_of_power_elem = 0;
  for (int i = 0; i < mat_dims.rows * mat_dims.cols; i++)
  {
    sum_of_power_elem += mat_data[i] * mat_data[i];
  }
  return std::sqrt(sum_of_power_elem);
}


int find_pivot_row(const Matrix& rref_mat, int current_row, int lead)
{
  int rows = rref_mat.get_rows();

  for (int r = current_row; r < rows; ++r)
  {
    if (rref_mat(r, lead) != 0)
    {
      return r;
    }
  }

  return PIVOT_ROW_NOT_FOUND;  // Return -1 if no pivot row is found
}


void swap_rows(Matrix& rref_mat, int row1, int row2)
{
  int cols = rref_mat.get_cols();

  for (int c = 0; c < cols; ++c)
  {
    float temp = rref_mat(row1, c);
    rref_mat(row1, c) = rref_mat(row2, c);
    rref_mat(row2, c) = temp;
  }
}


void divide_row(Matrix& rref_mat, int row, float divisor)
{
  int cols = rref_mat.get_cols();

  for (int c = 0; c < cols; ++c)
  {
    rref_mat(row, c) /= divisor;
  }
}

void eliminate_rows(Matrix& rref_mat, int pivot_row, int lead)
{
  int rows = rref_mat.get_rows();
  int cols = rref_mat.get_cols();

  for (int r = 0; r < rows; ++r)
  {
    if (r != pivot_row)
    {
      float factor = rref_mat(r, lead);
      for (int c = 0; c < cols; ++c)
      {
        rref_mat(r, c) -= factor * rref_mat(pivot_row, c);
      }
    }
  }
}

void round_small_values(Matrix& rref_mat)
{
  int rows = rref_mat.get_rows();
  int cols = rref_mat.get_cols();
  for (int r = 0; r < rows; ++r)
  {
    for (int c = 0; c < cols; ++c)
    {
      if (fabs((double)rref_mat(r, c)) < VERY_SMALL_NUMBER)
      {
        rref_mat(r, c) = 0;
      }
    }
  }
}


Matrix Matrix::rref() const
{
  Matrix rref_mat(*this);  // Create a copy of the *this matrix
  int rows = rref_mat.get_rows();
  int cols = rref_mat.get_cols();

  int lead = 0;
  for (int r = 0; r < rows; ++r)
  {
    if (lead >= cols)
    {
      return rref_mat;
    }
    int pivot_row = find_pivot_row (rref_mat, r, lead);
    if (pivot_row == -1)
    {
      lead++;
      if (lead == cols)
      {
        return rref_mat;
      }
      r--;  // Retry the current row with the new lead column
      continue;
    }
    swap_rows (rref_mat, pivot_row, r);
    float pivot_val = rref_mat(r, lead);
    divide_row (rref_mat, r, pivot_val);
    eliminate_rows (rref_mat, r, lead);
    lead++;
  }
  round_small_values (rref_mat);
  return rref_mat;
}


int Matrix::argmax () const
{
  float max_num = mat_data[0];
  int max_num_ind = 0;
  for (int i = 0; i < mat_dims.rows * mat_dims.cols; ++i)
  {
    if (mat_data[i] > max_num) // only if bigger
    {
      max_num = mat_data[i];
      max_num_ind = i;
    }
  }
  return max_num_ind;
}


float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < mat_dims.rows * mat_dims.cols; i++)
  {
    sum += mat_data[i];
  }
  return sum;
}


Matrix Matrix::operator+ (const Matrix &other_mat) const
{
  // check if the other matrix in the same sizes of "this"
  if (mat_dims.rows != other_mat.mat_dims.rows ||
  mat_dims.cols != other_mat.mat_dims.cols)
  {
    throw std::length_error (SIZE_ERROR);
  }
  Matrix addition_mat (mat_dims.rows,mat_dims.cols);
    for (int i = 0; i < mat_dims.rows * mat_dims.cols; ++i)
    {
      float sum_of_two_mat = mat_data[i] + other_mat.mat_data[i];
      addition_mat.mat_data[i] = sum_of_two_mat;
    } 
  return addition_mat;
}


Matrix& Matrix::operator+= (const Matrix &other_mat)
{
  // check if the other matrix in the same sizes of "this"
  if (mat_dims.rows != other_mat.mat_dims.rows ||
  mat_dims.cols != other_mat.mat_dims.cols)
  {
    throw std::length_error (SIZE_ERROR);
  }
  for (int i = 0; i < mat_dims.rows * mat_dims.cols ; ++i)
  {
    mat_data [i] += other_mat.mat_data[i];
  }
  return *this;
}


Matrix& Matrix::operator= (const Matrix &other_mat)
{
  if (&other_mat == this)
  {
    return *this;
  }
  delete[] mat_data;
  mat_data = nullptr;
  mat_data = new float [other_mat.mat_dims.rows * other_mat.mat_dims.cols];
  mat_dims = {other_mat.mat_dims.rows, other_mat.mat_dims.cols};
  for (int i = 0; i < mat_dims.rows * mat_dims.cols; ++i)
  {
    mat_data[i] = other_mat.mat_data[i];
  }
  return *this;
}


float& Matrix::operator() (const int i, const int j)
{
  if (i >= mat_dims.rows || i < 0 || j >= mat_dims.cols || j < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE_ERROR);
  }
  return mat_data[i * mat_dims.cols + j];
}


const float& Matrix::operator() (const int i, const int j)const
{
  if (i >= mat_dims.rows || i < 0 || j >= mat_dims.cols || j < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE_ERROR);
  }
  return mat_data[i * mat_dims.cols + j];
}


float& Matrix::operator[](int k)
{
  if (k >= mat_dims.rows * mat_dims.cols || k < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE_ERROR);
  }
  return mat_data[k];
}


const float& Matrix::operator[](int k) const
{
  if (k >= mat_dims.rows * mat_dims.cols || k < 0)
  {
    throw std::out_of_range(OUT_OF_RANGE_ERROR);
  }
  return mat_data[k];
}


Matrix operator* (const Matrix& r_mat, const Matrix& l_mat)
{
  // check if the other matrix can be multiply by this matrix
  if (r_mat.mat_dims.cols !=l_mat.mat_dims.rows)
  {
    throw std::length_error (SIZE_ERROR);
  }
  Matrix multi_mat (r_mat.mat_dims.rows, l_mat.mat_dims.cols);
  for (int i = 0; i < multi_mat.mat_dims.rows ; i++)
  {
    for (int j = 0; j < multi_mat.mat_dims.cols; j++)
    {
      float element = 0;
      for (int k = 0; k < r_mat.mat_dims.cols; k++)
      {
        element += (r_mat(i,k) * l_mat(k, j));
      }
      multi_mat(i, j) = element;
    }
  }
  return multi_mat;
}


Matrix Matrix::operator* (float c)
{
  Matrix new_mat = (*this);
  for (int i = 0; i < mat_dims.rows * mat_dims.cols ; i++)
  {
    new_mat[i] *= c;
  }
  return new_mat;
}


Matrix operator* (float c, const Matrix& mat)
{
  Matrix new_mat = mat;
  for (int i = 0; i < new_mat.get_rows() * new_mat.get_cols() ; i++)
  {
    new_mat[i] *= c;
  }
  return new_mat;
}


ostream& operator<<(ostream& s, const Matrix& mat)
{
  for (int i = 0 ; i < mat.mat_dims.rows ; i++)
  {
    for (int j = 0; j < mat.mat_dims.cols ; j++)
    {
      if (mat(i,j) > BIG_ENOUGH)
      {
        s << "**"; // double asterisk
      }
      else
      {
        s << "  "; // double space
      }
    }
   s <<"\n";
  }
  return s;
}


istream& operator>>(istream& input_s, Matrix& mat)
{
  for (int i = 0; i < mat.mat_dims.rows ; i++)
  {
    for (int j = 0; j < mat.mat_dims.cols; j++)
    {
      if (input_s.eof()) // input stream too small
      {
        throw std::runtime_error(STREAM_ERROR);
      }
      input_s.read ((char *)&mat(i,j), sizeof (float ));
    }
  }
  return input_s;
}


