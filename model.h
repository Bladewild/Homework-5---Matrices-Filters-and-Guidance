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
*   Model simulates lunar lander
*   Pid controller is public for easy access
*   
*   
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
  //BaseFilter<double>& filter;
  //static DummyFilter<double> default_filter;



public:

  /*!
  * Controller is public so that the user can control the
  * the smodelnal rate
  */
  PID controller;


  /*!
  * @brief Default Constructor
  * @brief h=0.1,setpoint pi/8 or 3.14159265358979323846 / 8
  * @brief state(0,0,0) R=4 I= 100000 d=(0.0, 7.0)
  * @brief K {4000, 100, 6000}
  * @post creates model object with default values
  */
  model();


  /*!
  * @brief 
  * @param[in] i_h step_size
  * @param[in] i_R
  * @param[in] i_I 
  * @param[in] i_desiredtheta theta to move to
  * @param[in] i_state starting values for model
  * @param[in] i_K K gains for PID controller
  * @pre all values should be reasonable in context
  * @post creates model object with given values
  * @note normal distribution cannot be changed
  */
  model(double i_h, double i_R, double i_I, double i_desiredtheta,
    const vector<double>& i_state, const vector<double>& i_K);

  /*! 
  * @brief copy constructor
  * @param[in] othermodel to be copied from
  * @post copies contents from othermodel to this
  */

  model(const model& o);

  /*!
  * @brief step function
  * @post steps model by h
  * @post calculates new state given u signal calculate
  * @throw invalid_argument I cannot be 0. Divide by 0"
  */

  void operator()();

  /*!
  * @brief adds noise up to 25% error
  * @post adds up to 25% percentage noise based on normal distribution
  */
  void addNoise();


  /*!
  * @brief filters noise of the assumed noisy measured state
  * @pre state of this model has to be noisy for filter to work
  * @pre filter must already be ready filter for this state
  * @pre filter must use op(vector<double> state) to filter state
  * @post filters noise of current state by passed in filter
  */
  void filterNoise(BaseFilter<double>& filter);

  /*!
  * @brief calculates new state given force
  * @param[in] input_force u signal
  * @post calculates new state given input_force value
  * @throw invalid_argument I cannot be 0. Divide by 0"
  */
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


  /*!
  * @brief returns latest Theta value
  * @post gets Theta from state
  */
  double getTheta() const;
};


#endif
