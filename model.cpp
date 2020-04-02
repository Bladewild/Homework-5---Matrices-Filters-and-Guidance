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
#include "dummyfilter.h"

DummyFilter<double> model::default_filter;

model::model() :
  h(0.1),
  R(4),
  I(100000),
  state(vector<double>{0, 0, 0}),
  d(0.0, 7.0),
  filter(default_filter),
  controller(PID((3.14159265358979323846 / 8), h,
    vector<double>{4000, 100, 6000}))
{}

//vector<double>{ 4000, 100, 6000})),
/*
model::model(double input_desire, double step_size, const vector<double> & v_inputP,
  const vector<double>& v_inputRates,const vector<double> & v_inputBase,
  const vector<double> & v_inputState,const vector<double>& v_Kinput):
  h(step_size), p(v_inputP),
  vRates(v_inputRates), vBase(v_inputBase), state(v_inputState)
{}*/

model::model(const model& o) :
  h(o.h), R(o.R), I(o.I), state(o.state),filter(o.filter)
{}



void model::operator()()
{
  //calculate U;
  double force=controller(state[0]); //passing theta to get force
  calculateState(force);
  addNoise();
  filterNoise();
}


void model::filterNoise()
{
  state = filter(state);
}

void model::altfilterNoise(BaseFilter<double>& i_f)
{
  state = i_f(state);
}


void model::calculateState(double input_force)
{
  double alpha = (R * input_force) / I;
  double omega = state[1] + (alpha * h);
  double theta = state[0] + (omega * h);
  //double theta = state[2] + (state[1] * h) + (omega * h);

  state[2] = alpha;
  state[1] = omega;
  state[0] = theta;

  //cout << "---------STATE---------" << endl;
  //cout << state[2] << endl;
  //cout << state[1] << endl;
  //cout << state[0] << endl;
  //cout << "---------STATE---------" << endl;
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



ostream& operator<<(ostream& os, const model& Obj)
{
  os.precision(8); // as requested
  //os <<"Alpha: "<< Obj.state[0]<<", "
  //   <<"Omega: " << Obj.state[1] << ","
  //   <<"Theta: "<< Obj.state[2] <<"\n";
  os << Obj.state[2] << ","<< Obj.state[1] << "," << Obj.state[0] << "\n";
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
    filter = source.filter; //check later
  }

  return *this;
}


