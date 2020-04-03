/*
* Author: Marky Santos-Tankia
* File: SPLP.hpp Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
* implementation file SLPLfilter
*/

#include "SPLPFilter.h"

template<typename T>
SLPLFilter<T>::SLPLFilter(vector<T> initial_state, double i_h, double i_f)
  : EMA(initial_state), h(i_h), f(i_f) {}

template<typename T>
vector<T> SLPLFilter<T>::operator()(vector<T> state, vector<T> control_vector)
{
  control_vector.donothing();
  double alpha = 1 - exp(-f * h);
  EMA = EMA * alpha + (1 - alpha) * state;
  return EMA;
}
