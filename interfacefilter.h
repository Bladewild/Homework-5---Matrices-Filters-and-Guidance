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
#ifndef INTERFACEFILTTER_H
#define INTERFACEFILTTER_H

#include "vector.h"

/*
* Class:
*/
template<typename T>
class Filter_Interface
{
public:
  virtual vector<T> operator()(vector<T> state, double signal_input) = 0;
};


#endif
