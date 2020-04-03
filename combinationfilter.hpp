/*
* Author: Marky Santos-Tankia
* File: combinationfilter.hpp Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
* implementation file of combinationfilter
*/

#include "combinationfilter.h"

template<typename T>
CombinationFilter<T>::CombinationFilter(std::initializer_list<BaseFilter<T>*> l): filters(l) {}

template<typename T>
vector<T> CombinationFilter<T>::operator()(vector<T> state, vector<T> control_vector)
{
  for (int i = 0; i < filters.size(); i++)
  {
    state = (*filters[i])(state, control_vector);
  }
  return state;
}