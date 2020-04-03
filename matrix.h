/*
* Author: Marky Santos-Tankia
* File: matrix.h Date: 
* Class: CS 5201
* Instructor : Clayton Price
*
* matrix file
*/

/*! \file
 *
 * A matrix library.
 */

#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <sstream> 
#include <functional>
#include "vector.h"
#include <math.h>  

using std::string;
using std::ostream;
using std::cout;
using std::istream;

/*
* Class: 
*/
template<typename T>
class matrix
{
private:
  vector<T>* grid;
  int current_cols;      
  int current_rows;     

  /*!
  * @brief initializes matrix
  * @param[in]  input_size integer
  * @pre  input_rows is non negative
  * @pre  input_coloumns is non negative
  * @post creates new matrix specified by input_rows, input_coloumns
  * @throw invalid_argument if input_size is negative
  */

  void init(int input_rows, int input_coloumns);

  /*!
  * @brief Does operations for two T types
  * @param[in] left T type
  * @param[in] right T type
  * @param[in] symbol char arithmetic sign
  * @pre left and right matrix must be same dimensions
  * @pre T = T (assignment) must be defined.
  * @pre T + T (assignment) must be defined.
  * @pre T - T (assignment) must be defined.
  * @post return result of type T of the left
  * @post and right arithmetic results
  * @throw invalid_argument if symbol not supported
  */

  static matrix<T> plusminusHandler(const matrix<T>& lMat,
    const matrix<T>& rMat, const char& symbol);

  //PUBLIC------------------------------
public:

  /*!
  * @brief Constructs vector of specificied size
  * @brief  defaults to 0,0 size if input not passed
  * @param[in] row of int
  * @param[in] col of int
  * @pre size cannot be negative
  * @post creates vector of specified size
  */
  matrix(int row=0,int col=0);

  /*!
  * @brief creates matrix from 2d list
  * @param[in]  init_list 2D matrix
  * @pre  T = T (assignment) must be defined
  * @post copies elements from init_list to arr in order
  */

  matrix(std::initializer_list<std::initializer_list<T>> init_list);

  /*
  * @pre T = T (assingment) defined
  * @pre init preconditions
  */
    
  matrix(const matrix<T>& otherMatrix);

  int cols() const;
  int rows() const;

  template<typename U>
  friend ostream& operator << (ostream& os, const matrix<U>& Obj);

  template<typename U>
  friend istream& operator >> (istream& finput, matrix<T>& Obj);

  matrix<T>& operator = (const matrix<T>& source);

  ~matrix();

  //arithmetic
  template<typename U>
  friend matrix<U> operator+(const matrix<U>& lhs, const matrix<U>& rhs);
  template<typename U>
  friend matrix<U> operator-(const matrix<U>& lhs, const matrix<U>& rhs);
  matrix <T>& operator +=(const matrix<T>& rhs);
  matrix <T>& operator -=(const matrix<T>& rhs);

  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const U& rhsScalar);
  template<typename U>
  friend matrix<U> operator*(const U& lhsScalar , const matrix<U>& rhs);

  T& operator()(const int i, const int j);
  T operator()(const int i, const int j) const;


  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const matrix<U>& rhs);

  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const vector<U>& rhs);

  template<typename U>
  friend matrix<U> operator*(const vector<U>& lhs, const  matrix<U>& rhs);
  
  matrix<T> operator-() const;

  static matrix<T> identity(int size);
  matrix<T> transpose() const;
  matrix<T> invert() const;


  /*!
  * @brief returns frobenius norm
  * @pre 
  * @pre  T+= T defined
  * @pre  T *T  defined
  * @post returns frobenius norm
  */
  explicit operator double() const;
};


#include "global.h"
#include "matrix.hpp"


#endif
