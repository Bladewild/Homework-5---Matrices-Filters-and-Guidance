/*
* Author: Marky Santos-Tankia
* File: dummyfilter.h Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
*
*/
/*! \file
 *
 *
 */
#ifndef DUMMYTFILTER_H
#define DUMMYTFILTER_H

#include "vector.h"
#include "basefilter.h"

 /*
 * Class:
 *   Dummyfilter, Doesn't filter anything, returns state
 */

template<typename T>
class DummyFilter: public BaseFilter<T>
{
public:
  DummyFilter<T>() = default;

  /*!
  * @brief literally does nothing
  * @brief returns state in original form
  */
  virtual vector<T> operator()(vector<T> state, vector<T> control_vector);
};

#include "dummyfilter.hpp"
#endif
