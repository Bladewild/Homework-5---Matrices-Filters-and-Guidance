/*
* Author: Marky Santos-Tankia
* File: dummyfilter.h Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
* Implementation dummy filter 
*/

#include "dummyfilter.h"

template<typename T>
vector<T> DummyFilter<T>::operator()(vector<T> state, vector<T> control_vector)
{
  control_vector.donothing();
  return state;
}


