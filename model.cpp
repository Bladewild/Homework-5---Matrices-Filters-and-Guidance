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
  controller(PID((3.14159265358979323846/8),h,
    vector<double>{ 5, 0.05, 0.05}))
{}
/*
model::model(double input_desire, double step_size, const vector<double> & v_inputP,
  const vector<double>& v_inputRates,const vector<double> & v_inputBase,
  const vector<double> & v_inputState,const vector<double>& v_Kinput):
  h(step_size), p(v_inputP),
  vRates(v_inputRates), vBase(v_inputBase), state(v_inputState)
{}*/

model::model(const model& o) :
  h(o.h), R(o.R), I(o.I), state(o.state)
{}



void model::operator()()
{
  //calculate U;
  double force=controller(state[2]); //passing theta to get force
  calculateState(force);
}


void model::operator()(double input_step)
{
   if (input_step <= 0)
  {
    throw std::invalid_argument("input_step cannot be < 0 or = 0");
  }
  double force = controller(state[2]); //passing theta to get force
  calculateState(force);
}

void model::calculateState(double input_force)
{
  double alpha = (R * input_force) / I;
  double omega = state[1] + (alpha * h);
  double theta = state[2] + (omega * h);

  state[0] = alpha;
  state[1] = omega;
  state[2] = theta;
}

ostream& operator<<(ostream& os, const model& Obj)
{
  os.precision(8); // as requested
  os <<"Alpha: "<< Obj.state[0]<<", "
     <<"Omega: " << Obj.state[1] << ","
     <<"Theta: "<< Obj.state[2] <<"\n";
  //os << Obj.state[0] << ","<< Obj.state[1] << "\n";
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
  }

  return *this;
}


