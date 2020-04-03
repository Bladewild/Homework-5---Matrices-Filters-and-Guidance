/*
* Author: Marky Santos-Tankia
* File: PID.h Date: 4/3/20
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
  double latestU;
  vector<double> K_GAINS;


public:

  enum K : int { P = 0, I = 1, D = 2 };

  /*!
  * @brief uses default c++ implementation
  * @brief useful for initializing and assign later.
  */
  PID() = default;

  /*!
  * @brief constructor
  * @param[in] i_desired value to move to
  * @param[in] i_h step_size
  * @param[in] i_K K gains values
  * @pre i_h value must be non-negative non zero
  * @pre i_K should be reasonable in context for model (so no negatives)
  * @post creates PID controller based on given values
  */
  PID(double i_desired, double i_h, vector<double> i_K) :
    desired(i_desired), previousError(0), iError(0), h(i_h), latestU(0.0),
    K_GAINS(i_K)
  {};


  /*!
  * @brief copy constructor
  * @param[in] otherEuler
  * @post copies oPid content to this object to be constructed
  */
  PID(const PID& oPid) : desired(oPid.desired), previousError(oPid.previousError),
    iError(oPid.iError), h(oPid.h), latestU(oPid.latestU), K_GAINS(oPid.K_GAINS)
  {}



  /*!
  * @brief  returns value of element at position of vector K
  * @param[in]  index_var index position to access by K::P,K::I,K::D
  * @pre index_var must be bounded,non negative
  * @post returns value to element at given index_var
  * @post of vector K
  * @throw range_error if out of bounds (vector class)
  * @throw range_error vector is empty (vector class)
  */

  double operator[](const K index_var) const;

  /*!
  * @brief  returns reference of element at position of vector K
  * @param[in]  index_var index position to access by K::P,K::I,K::D
  * @pre index_var must be bounded,non negative
  * @post returns reference to element at given index_var
  * @post of vector K
  * @throw range_error if out of bounds (vector class)
  * @throw range_error vector is empty (vector class)
  */

  double& operator [] (const K index_var);

  /*
  * @brief calculates u signal given state
  * @pre step_size h cannot be initialized to <0 or = 0
  * @post calculates u signal given state
  * @throw invalid_argument if 0 or negative h
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
  * @param[in] setPoint theta to set to
  * @pre setPoint (must be reasonable in context)
  * @post sets desired value to move 
  * @post iError is reset
  * @throw invalid_argument when setPoint<=0
  */

  void reset(double setPoint);

  /*!
  * @brief returns latestU value
  * @pre stepfunction must have calculated recently
  * @post gets lastestU calculated from stepfunction
  */
  double getU();

};


#endif
