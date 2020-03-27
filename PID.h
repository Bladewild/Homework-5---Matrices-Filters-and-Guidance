/*
* Author: Marky Santos-Tankia
* File: PID.h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* PID file
*/
/*! \file
 *
 * A PID library.
 */
#ifndef PID_H
#define PID_H


#include <iostream>
#include <string>
#include <functional>
#include "vector.h"
#include "global.h"
#include <random>

using std::string;
using std::cout;
using std::endl;
using std::function;


enum Range : int { first = 0, second = 1, third = 2 };
/*
* Class: PID
*   Controller of the module
*   Creates a u signal from error calculated
*/
class PID
{
private:
  //pid
  //in our case, the difference between the desired and actual blood glucose levels)
  double desired;
  double previousError;
  double iError;
  double h;
  vector<double> K;


public:
  /*!
  * @brief uses default c++ implementation
  * @brief useful for initializing and assign later.
  */
  PID() = default;

  /*!
  * @brief constructor
  * @param[in] 
  * @pre
  * @pre
  * @pre input_stepSize >0
  * @post 
  */
  PID(double i_desired, double i_h,vector<double> i_K):
    desired(i_desired),previousError(0), iError(0),h(i_h),K(i_K)//input here
  {};


  /*!
  * @brief copy constructor
  * @param[in] otherEuler
  * @post copies Euler content to this object to be constructed
  */
  PID(const PID& oPid) : desired(oPid.desired), previousError(oPid.previousError),
    iError(oPid.iError), h(oPid.h), K(oPid.K)
  {}



  /*!
  * @brief  returns value of element at position of vector K
  * @param[in]  index_var index position to access------------------------------------
  * @pre index_var must be bounded,non negative
  * @post returns value to element at given index_var
  * @post of vector K
  * @throw range_error if out of bounds (vector class)
  * @throw range_error vector is empty (vector class)
  */

  double  operator[](Range index_var) const;

  /*!
  * @brief  returns reference of element at position of vector K
  * @param[in]  index_var index position to access------------------------------------------
  * @pre index_var must be bounded,non negative
  * @post returns reference to element at given index_var
  * @post of vector K
  * @throw range_error if out of bounds (vector class)
  * @throw range_error vector is empty (vector class)
  */

  double& operator [] (const Range index_var);

  /*
  * @brief
  * @post 
  * @post 
  */

  double operator()(double state);



  /*!
  * @brief assignment operator
  * @param[in] source PID object
  * @post copies source's content to *this
  */
  PID & operator = (const PID& source);

  

  /*!
  * @brief reset setpoint
  * @param[in] setPoint Glucose to set to
  * @pre setPoint >0
  * @post sets desiredGlucose of model
  * @post to setPoint
  * @throw invalid_argument when setPoint<=0
  */

  void reset(double setPoint);

};


#endif
