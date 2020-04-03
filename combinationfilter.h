/*
* Author: Marky Santos-Tankia
* File: combinationfilter.h Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
* class file of combinationfilter
*/
/*! \file
 *
 *  Declares the constructor and method of filter
 */
#ifndef COMBINATIONFILTER_H
#define COMBINATIONFILTER_H

#include "basefilter.h"
#include "vector.h"
 /*
 * Class: CombinationFilter
 *    Combines filters gained from initilization list
 *    their are applied through initialization order.
 *    Filters are passed by reference. Meaning filters can
 *    if the original filter was changed.
 */
template<typename T>
class CombinationFilter : public BaseFilter<T>
{
  vector<BaseFilter<T>*> filters;
public:
  /*!
  * @brief kalman filter, constructor
  * @param[in] l initialization list of ref Basefilter<T>
  * @pre  filters passed must not change unless user specifically intends
  * @pre  to change filters (since they are passed by reference)
  * @post creates CombinationFilter object
  */
  CombinationFilter(std::initializer_list<BaseFilter<T>*> l);
  /*!
  * @brief combination filter, applies filter in order initialized
  * @brief and state given.
  * @param[in] control_vector any control parameters user may pass
  * depends on filter
  * @param[in] state current measurement of the system (that has noise)
  * @pre filter preconditions
  * @post applies list filter of filters to state
  */
  virtual vector<T> operator()(vector<T> state, vector<T> control_vector);
};

#include "combinationfilter.hpp"

#endif
