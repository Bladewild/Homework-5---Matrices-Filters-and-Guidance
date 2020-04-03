/*
* Author: Marky Santos-Tankia
* File: kalmanfilter.h Date: 4/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* Kalman filter class
*/
/*! \file
 *
 * Kalmanfilter
 */
#ifndef KALMANTFILTER_H
#define KALMANTFILTER_H

#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "basefilter.h"
#include "PID.h"
#include <functional>
 /*
 * Class: Kalmanfilter
 *  kalmanfilter class. Uses predicted model and
 *  measured to make new state.
 */

template<typename T>
class Kalmanfilter : public BaseFilter<T>
{
private:
  matrix<T> A;
  matrix<T> B;
  vector<T> current_state_estimate; // Initial state estimate.
  matrix<T> current_prob_estimate; //Initial covariance estimate.
  matrix<T> R; //Estimated error in measurements.
  //vector<T> control_vector;

public:
  /*!
  * @brief kalman filter, constructor
  * @param[in] _A State Transition Matrix
  * @param[in] _B Control Matrix
  * @param[in] _x Initial state value
  * @param[in] _P Initial covariance matrix
  * @param[in] _R Estimated error in measurements.
  * @pre matrices have to be comptable with their x and u vertices
  * @pre matrices x matrices must be compatible
  * @pre (row x coloumn requirement for multiplcation/dot to work)
  * @pre Matrices in +,- must operation must have equal dimensions 
  * @post creates Kalmanfilter object
  */
  Kalmanfilter(matrix<T> _A, matrix<T> _B, vector<T> _current_x,
    matrix<T>_P, matrix<T> _R);

  /*!
  * @brief kalman filter, filters out noise based on model predicted
  * @brief and state given.
  * @param[in] control_vector latest u value for the control
  * @param[in] state current measurement of the system (that has noise)
  * @pre artihmetic operators T * T,T - T,T + T must be defined
  * @pre Seyeplusone must become a well conditioned matrix
  * @post filters noise of state
  * @note blocks of code are not in seperate functions 
  * @note to reduce unncessary constructing and copying of matrixes
  */

  virtual vector<T> operator()(vector<T> state, vector<T> control_vector);  
};
#include "kalmanfilter.hpp"

#endif
