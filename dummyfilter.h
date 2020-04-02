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
#ifndef DUMMYTFILTER_H
#define DUMMYTFILTER_H

#include "vector.h"
#include "basefilter.h"

 /*
 * Class:
 */

template<typename T>
class DummyFilter: public BaseFilter<T>
{
public:
  DummyFilter<T>() = default;
  virtual vector<T> operator()(vector<T> state)
  {
    //cout << "FILTER1\n";
    return state;
  }

};


#endif
