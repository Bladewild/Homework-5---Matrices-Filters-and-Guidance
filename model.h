/*
* Author: Marky Santos-Tankia
* File: model.h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* model file
*/

/*! \file
 *
 * A model emulation library.
 */
#ifndef model_H
#define model_H


#include <iostream>
#include <functional>
#include "vector.h"
#include "PID.h"
#include <algorithm>    // std::max

using std::cout;
using std::function;
using std::ostream;


/*
* Class: model
*/
class model
{
private:

  double h;
  double R;
  double I;
  vector<double> state;

public:

  //Appropriate constructors/destructors/copy functionality
  //Function evaluation operator () that “steps” the model, calculating a new state given the thruster force input
  //A means of writing the current state of the model to a std::ostream (stream operator), using the format Alpha: <alpha>, Omega: <omega>, Theta: <theta>
  //A means of interacting with a PID controller to send the current state and receive the thruster force
  //A means of using any filter derived from your filter interface base to filter the “measured” state prior to sending it to the controller
  /*!
  * Controller is public so that the user can control the
  * the smodelnal rate
  */
  PID controller;


  /*!
  * @brief Default Constructor
  * @brief
  * @post creates model object with default values
  */
  model();


  /*!
  * @brief 
  * @param[in] i
  * @pre
  * @post 
  */
  //model();

  /*! 
  * @brief copy constructor
  * @param[in] othermodel to be copied from
  * @post copies contents from othermodel to this
  */

  model(const model& o);

  /*!
  * @brief steps default h
  * @post steps controller by h, updates Rates
  * @post steps Euler object with default step (h)
  */

  void operator()();

  /*!
  * @brief steps given input_step
  * @param[in] input_step non zero step positive number
  * @post steps controller by input_step, updates Rates
  * @post steps Euler object with input_step given
  */
  void operator()(double input_step);

  /*!
  * @brief outputs state vector values of Obj
  * @param[in] os ostream object
  * @param[in] Obj model object to print values from
  * @post prints values in form
  */


  void calculateState(double input_force);

  friend ostream& operator << (ostream& os, const model& Obj);

  /*!
  * @brief copies source contents to this object
  * @param[in] source model reference
  * @post copies contents of model to this if not same
  */

  model& operator = (const model& source);
};


#endif
