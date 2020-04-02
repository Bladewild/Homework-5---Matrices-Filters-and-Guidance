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
#include <random>
#include "basefilter.h"
#include "dummyfilter.h"
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
  std::normal_distribution<double> d;
  std::default_random_engine RNG;
  BaseFilter<double>& filter;
  static DummyFilter<double> default_filter;

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
  * @brief
  * @pre
  * @post 
  */
  void addNoise();

  /*!
  * @brief
  * @pre
  * @post
  */
  void filterNoise();

  void altfilterNoise(BaseFilter<double>& i_f);

  void calculateState(double input_force);
  /*!
  * @brief outputs state vector values of Obj
  * @param[in] os ostream object
  * @param[in] Obj model object to print values from
  * @post prints values in form
  */

  friend ostream& operator << (ostream& os, const model& Obj);

  /*!
  * @brief copies source contents to this object
  * @param[in] source model reference
  * @post copies contents of model to this if not same
  */

  model& operator = (const model& source);
};


#endif
