/*
* Author: ALAIN MARKUS SANTOS-TANKIA
* File: PID.cpp Date: 3/13/20
* Class: CS 5201
* Instructor : CLATON PRICE
*
* Implementation file of PID
*/

#include "PID.h"


double PID::operator()(double state)
{
  if (h <= 0)
  {
    throw std::invalid_argument("step size cannot be < 0 or = 0");
  }

  double error = desired - state;
  iError += 0.5 * (h) * (previousError + error);
  double dError = (error-previousError)/h;
  double P = K_GAINS[0] * error;
  double I = K_GAINS[1] * iError;
  double D = K_GAINS[2] * dError;

  double u= (P + I + D);
  previousError = error;

  latestU = u;
  return u;
}


PID& PID::operator = (const PID& source)
{
  if (this != &source)
  {
    desired = source.desired;
    previousError = source.previousError;
    iError = source.iError;
    h = source.h;
    K_GAINS = source.K_GAINS;
    latestU = source.latestU;
  }
  return *this;
}



double PID::operator[](const K index_var) const
{
  if (0 > index_var ||index_var>2)
  {
    throw std::invalid_argument("out of bounds.");
  }
  return K_GAINS[index_var];
}

double& PID::operator[](const K index_var)
{
  if (0 > index_var || index_var > 2)
  {
    throw std::invalid_argument("out of bounds.");
  }
  return K_GAINS[index_var];
}
/*
double PID::operator[](Range index_var) const
{
  return K[index_var];
}

double& PID::operator[](const Range index_var)
{
  return K[index_var];
}
*/
/*
constexpr bool PID::checkIndex(int index_var, int min, int max) const
{
  if (index_var < min || index_var>max)
  {
    return true;
  }
  return false;
}
*/
//just the type would change
//price opreator[] enum type

void PID::reset(double setPoint)
{
  if (setPoint <= 0)
  {
    throw std::invalid_argument("Set point cannot be <=0");
  }
  iError = 0;
  desired = setPoint;
}

double PID::getU()
{
  return latestU;
}
