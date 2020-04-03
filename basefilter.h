/*
* Author: Marky Santos-Tankia
* File: basefilter.h Date: 4/3/20
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
 * Class: BaseFilter
 *  This is used to have filters be used in many functions
 */
template<typename T>
class BaseFilter //: public Filter_Interface<T>
{
public:

  /*!
  * @brief pure virtual function, main filter function
  * @param[in] control_vector latest u value for the control
  * @param[in] state current measurement of the system
  * @post filters noise of state
  */
  virtual vector<T> operator()(vector<T> state, vector<T> control_vector) = 0;
};


#endif
