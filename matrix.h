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
  */

  void init(int input_rows, int input_coloumns);

  static matrix<T> plusminusHandler(const matrix<T>& lMat,
    const matrix<T>& rMat, const char& symbol);

  //PUBLIC------------------------------
public:

  matrix(int row=0,int col=0);
  //A constructor accepting a two-dimensional std::initializer_list
  matrix(std::initializer_list<std::initializer_list<T>> init_list);

  /*
  * @pre T = T (assingment) defined
  * @pre init preconditions
  */
    
  matrix(const matrix<T>& otherMatrix);

  template<typename U>
  friend ostream& operator << (ostream& os, const matrix<U>& Obj);

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

  int cols() const;
  int rows() const;

  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const matrix<U>& rhs);

  //matrix<T> invert();

  matrix<T> operator-() const;

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
