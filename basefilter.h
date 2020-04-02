/*
* Author: Marky Santos-Tankia
* File: .h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* 
*/
/*! \file
 *
 * 
 */
#ifndef BASEFILTTER_H
#define BASEFILTTER_H

#include "vector.h"

/*
* Class:
*/
template<typename T>
class BaseFilter
{
public:
  virtual vector<T> operator()(vector<T> state) = 0;
};


#endif
