/*
* Author: ALAIN MARKUS SANTOS-TANKIA
* File: model.cpp Date: 3/13/20
* Class: CS 5201
* Instructor : CLATON PRICE
*
* Implementation file of model
*/


#include "model.h"
//h=0.1
//setpoint pi/8 radians
// state(0,0,0)
//R= 4m
//I= 100000kg⋅m2 


model::model() :
  h(0.1),
  R(4),
  I(100000),
  state(vector<double>{0, 0, 0}),
  d(0.0, 7.0),
  //filter(default_filter),
  controller(PID((3.14159265358979323846 / 8), h,
    vector<double>{4000, 100, 6000}))
{}

model::model(double i_h, double i_R, double i_I, double i_desiredtheta,
  const vector<double>& i_state, const vector<double>& i_K):
  h(i_h), R(i_R),I(i_I), state(i_state),d(0.0,7.0),
  controller(PID(i_desiredtheta,i_h,i_K))
{}

model::model(const model& o) :
  h(o.h), R(o.R), I(o.I), state(o.state)
{}



void model::operator()()
{
  //calculate U;
  double force=controller(state[0]); //passing theta to get force
  calculateState(force);
}





void model::calculateState(double input_force)
{
  if (I == 0)
  {
    throw std::invalid_argument("I cannot be 0. Divide by 0");
  }
  double alpha = (R * input_force) / I;
  double omega = state[1] + (alpha * h);
  double theta = state[0] + (omega * h);
  
  state[2] = alpha;
  state[1] = omega;
  state[0] = theta;
}

void model::addNoise()
{
  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  double percentageNoise;
  do
  {
    percentageNoise = d(RNG);
  } while (!(percentageNoise >= -25.0 && percentageNoise <= 25.0));
  percentageNoise /= 100.0;
  //add noise based on percentage
  state[0] += state[0] * percentageNoise;
  state[1] += state[1] * percentageNoise;
  state[2] += state[2] * percentageNoise;
}

void model::filterNoise(BaseFilter<double>& filter)
{
  state = filter(state, { 0,0,controller.getU() });
}

ostream& operator<<(ostream& os, const model& Obj)
{
  os.precision(8); // as requested
  os <<"Alpha: "<< Obj.state[2]<<", "
     <<"Omega: " << Obj.state[1] << ","
     <<"Theta: "<< Obj.state[0] <<"\n";
  return os;
}

model& model::operator=(const model& source)
{
  if (this != &source)
  {
    h = source.h;
    R = source.R;
    I = source.I;
    state = source.state;
    d = source.d;
    RNG = source.RNG;
  }

  return *this;
}


double model::getTheta() const
{
  return state[0];
}