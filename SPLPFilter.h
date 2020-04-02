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
#ifndef SLPLFILTER_H
#define SLPLFILTER_H

#include "vector.h"
#include "basefilter.h"

 /*
 * Class:
 */
template<typename T>
class SLPLFilter : public BaseFilter<T>
{
private:
  vector<T> EMA;
  double h;
  double f;
public:


  SLPLFilter(vector<T> initial_state,double i_h,double i_f) : EMA(initial_state),h(i_h),f(i_f){}

  virtual vector<T> operator()(vector<T> state)
  {
    //cout << "FILTER2\n";
    double alpha = 1 - exp(-f * h);
    EMA = EMA*alpha +(1-alpha)*state;
    return EMA;
  }

};


#endif
