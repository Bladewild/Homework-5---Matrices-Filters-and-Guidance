/*
* Author: ALAIN MARKUS SANTOS-TANKIA
* File: matrix.hpp Date: 3/13/20
* Class: CS 5201
* Instructor : CLATON PRICE
*
* Implementation file of matrix
*/

#include "matrix.h"


template<typename T>
matrix<T>::matrix(int row,int col)
{
  init(row,col);
}



template<typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> init_list)
{
  //throw an error if incorrect sizing
  int col = (init_list.begin())->size();
  int row = init_list.size();
  init(row,col);

  int index_y = 0;
  for (auto y : init_list)
  {
    int index_x = 0;
    for (auto x : y)
    {
      grid[index_y][index_x] = x;
      index_x++;
    }
    index_y++;
  }
}

template<typename T>
void matrix<T>::init(int input_rows,int input_coloumns)
{
  if (input_rows < 0 || input_coloumns < 0)
  {
    cout << input_rows << " " << input_coloumns;
    throw std::invalid_argument(" cannot be a negative number.");
  }
  current_cols = input_coloumns;
  current_rows = input_rows;
  grid = new vector<T>[input_rows];
  for (int i = 0; i < input_rows; i++)
  {
    grid[i].resize(input_coloumns);
  }
}

template<typename T>
matrix<T>::matrix(const matrix<T>& otherMatrix)
{
  init(otherMatrix.current_rows, otherMatrix.current_cols);
  
  for(int y=0;y< otherMatrix.current_rows;y++)
  {
    for (int x = 0; x < otherMatrix.current_cols; x++)
    {
      grid[y][x]= otherMatrix.grid[y][x];
    }
  }

}

//--------------OPERATORS------------------
template<typename T>
matrix<T>& matrix<T>::operator = (const matrix<T>& source)
{
  if (this != &source)
  {
    if (grid != nullptr)
    {
      delete[] grid;
    }
    init(source.current_rows, source.current_cols);
    for (int y = 0; y < source.current_rows; y++)
    {
      for (int x = 0; x < source.current_cols; x++)
      {
        grid[y][x] = source.grid[y][x];
      }
    }

  }
  return *this;
}

//------------------------ARITHMATRIC-----------
// a rowx col b multiplication
template<typename T>
matrix<T> operator+(const matrix<T>& lhs, const matrix<T>& rhs)
{
  char symbol = '+';
  return matrix<T>::plusminusHandler(lhs, rhs, symbol);
}
template<typename T>
matrix<T> operator-(const matrix<T>& lhs, const matrix<T>& rhs)
{
  char symbol = '-';
  return matrix<T>::plusminusHandler(lhs, rhs, symbol);
}

template<typename T>
matrix <T>& matrix<T>::operator +=(const matrix<T>& rhs)
{
  char symbol = '+';
  *this = matrix<T>::plusminusHandler(*this, rhs, symbol);

  return (*this);
}

template<typename T>
matrix < T>& matrix<T>::operator -=(const matrix<T>& rhs)
{
  char symbol = '-';
  *this = matrix<T>::plusminusHandler(*this, rhs, symbol);
  return (*this);
}

template<typename T>
matrix<T> matrix<T>::plusminusHandler(const matrix<T>& lMat,
  const matrix<T>& rMat, const char& symbol)
{
  //check if unequal
  if ((lMat.current_cols != rMat.current_cols) 
    && (lMat.current_rows != rMat.current_rows))
  {
    throw std::invalid_argument("matrix sizes are unequal");
  }

  int temp_cols = lMat.current_cols;
  int temp_rows = lMat.current_rows;

  matrix<T> new_m(temp_rows, temp_cols);

  for (int y = 0; y < temp_rows; y++)
  {
    for (int x = 0; x < temp_cols; x++)
    {
      if (symbol == '+')
      {
        new_m.grid[y][x] = lMat.grid[y][x] + rMat.grid[y][x];
      }
      else
      {
        new_m.grid[y][x] = lMat.grid[y][x] - rMat.grid[y][x];
      }
    }
  }
  return new_m;
}
//------------SCALAR
template<typename T>
matrix<T> operator*(const T& lhsScalar, const matrix<T>& rhs)
{
  if (rhs.current_cols < 0 || rhs.current_rows <0)
  {
    throw std::invalid_argument("matrix col or row is < 0");
  }
  int temp_cols = rhs.current_cols;
  int temp_rows = rhs.current_rows;

  matrix<T> new_m(temp_rows, temp_cols);

  for (int y = 0; y < temp_rows; y++)
  {
    for (int x = 0; x < temp_cols; x++)
    {
      new_m.grid[y][x] = lhsScalar* rhs.grid[y][x];
    }
  }
  return new_m;
}

template<typename T>
matrix<T> operator*(const matrix<T>& lhs, const T& rhsScalar)
{
  if (lhs.current_cols < 0 || lhs.current_rows < 0)
  {
    throw std::invalid_argument("matrix col or row is < 0");
  }
  int temp_cols = lhs.current_cols;
  int temp_rows = lhs.current_rows;

  matrix<T> new_m(temp_rows, temp_cols);

  for (int y = 0; y < temp_rows; y++)
  {
    for (int x = 0; x < temp_cols; x++)
    {
      new_m.grid[y][x] = rhsScalar * lhs.grid[y][x];
    }
  }
  return new_m;
}
//MATRIX MULTIPILICATION
template<typename T>
matrix<T> operator*(const matrix<T>& lhs, const matrix<T>& rhs)
{
  if (lhs.current_cols != rhs.current_rows)
  {
    throw std::invalid_argument("left matrix col and right matrix row is unequal");
  }
  int temp_cols = rhs.current_cols;
  int temp_rows = lhs.current_rows;

  matrix<T> new_m(temp_rows, temp_cols);



  for (int i = 0; i < lhs.current_rows; i++)
  {
    for (int j = 0; j < rhs.current_cols; j++)
    {
      new_m.grid[i][j] = 0;
      for (int k = 0; k < lhs.current_cols; k++)
      {
        new_m.grid[i][j] = new_m.grid[i][j] + (lhs.grid[i][k] * rhs.grid[k][j]);
      }
    }
  }

  return new_m;
}

template<typename T>
matrix<T> matrix<T>::operator-() const
{
  //check if vector is empty;
  if (current_rows == 0 || current_cols == 0)
  {
    throw std::range_error(" vector is empty");
  }

  matrix<T> new_m(current_rows, current_cols);

  for (int y = 0; y < current_rows; y++)
  {
    for (int x = 0; x < current_cols; x++)
    {
      new_m.grid[y][x] = -(grid[y][x]);
    }
  }
  return new_m;
}

//--------------------------------------



template<typename T>
matrix<T>::~matrix()
{
  if (grid != nullptr)
  {
    delete[] grid;
  }
}


template<typename T>
ostream& operator << (ostream& os, const matrix<T>& Obj)
{
  cout.precision(8); // as requested
  for(int y=0;y<Obj.current_rows;y++)
  {
    for (int x = 0; x < Obj.current_cols; x++)
    {
      os << Obj.grid[y][x] << " ";
    }
    if (y != Obj.current_rows - 1)
    {
      os << "\n";
    }
  }
  return os;
}

template<typename T>
T& matrix<T>::operator()(const int i,const int j)
{
  return grid[i][j];
}

template<typename T>
T matrix<T>::operator()(const int i, const int j) const
{
  return grid[i][j];
}

template<typename T>
int matrix<T>::cols() const
{
  return current_cols;
}

template<typename T>
int matrix<T>::rows() const
{
  return current_rows;
}

template<typename T>
matrix<T>::operator double() const
{
  double f_n = 0;

  for (int y = 0; y < current_rows; y++)
  {
    for (int x = 0; x < current_cols; x++)
    {
      f_n += grid[y][x] * grid[y][x];
    }
  }

  return std::sqrt(f_n);
}


template<typename T>
matrix<T> matrix<T>::invert() const
{
  //Identity matrix
  matrix<T> m_Identity(current_rows, current_cols);
  for (int i = 0; i < current_rows; i++)
  {
    for (int j = 0; j < current_cols; j++)
    {
      if (i == j)
      {
        m_Identity(i, i) = 1;
      }
      else
      {
        m_Identity(i, j) = 0;
      }
    }
  }
  matrix<T> xI;
  matrix<T> old_x = m_Identity;

  matrix<T> h = -old_x + (*this) * old_x * old_x;
  xI = old_x - h;
  matrix<T> outcome = (m_Identity - xI * (*this));
  double guess = static_cast<double>(outcome);
  while (guess >= 0.00001)
  {
    old_x = xI;
    h = -old_x + (*this) * old_x * old_x;
    xI = old_x - h;
    outcome = (m_Identity - xI * (*this));
    guess = static_cast<double>(outcome);
  }
  return xI;
}