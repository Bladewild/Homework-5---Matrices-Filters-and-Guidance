/*
* Author: Marky Santos-Tankia
* File: .h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* interface file of combinationfilter
*/
/*! \file
 *
 * interface for filters
 */
#ifndef BASEFILTTER_H
#define BASEFILTTER_H

//#include "interfacefilter.h"
#include "vector.h"

 /*
 * Class:
 *  This is used to have filters be used in many functions
 */
template<typename T>
class BaseFilter //: public Filter_Interface<T>
{
public:

  /*!
  * @brief kalman filter, filters out noise based on model predicted
  * @brief and state given.
  * @param[in] control_vector latest u value for the control
  * @param[in] state current measurement of the system (that has noise)
  * @pre artihmetic operators T * T,T - T,T + T must be defined
  * @post filters noise of state
  */
  virtual vector<T> operator()(vector<T> state, vector<T> control_vector) = 0;
};


#endif
