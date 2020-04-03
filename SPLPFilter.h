/*
* Author: Marky Santos-Tankia
* File: SPLP.h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
*
*/
/*! \file
 *
 *
 */
#ifndef SLPLFILTER_H
#define SLPLFILTER_H

#include "vector.h"
#include "basefilter.h"

 /*
 * Class:  single-pole low-pass filter
 *  (essentially expoonential moving average)
 */
template<typename T>
class SLPLFilter : public BaseFilter<T>
{
private:
  vector<T> EMA;
  double h;
  double f;
public:


  /*!
  * @brief Constructor
  * @pre h > 0
  * @post creates model object with default values
  */
  SLPLFilter(vector<T> initial_state, double i_h, double i_f);

  /*!
  * @brief filter function
  * @pre double * T (multiplication) must be defined
  * @pre T * double (multiplication) must be defined
  * @post filters out state and filtered out state
  */
  virtual vector<T> operator()(vector<T> state, vector<T> control_vector);

};
#include "SPLPFilter.hpp"

#endif
