﻿/*
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
  double P = K[0] * error;
  double I = K[1] * iError;
  double D = K[2] * dError;

  double u= (P + I + D);
  previousError = error;
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
    K = source.K;
  }

  return *this;
}

double PID::operator[](Range index_var) const
{
  return K[index_var];
}

double& PID::operator[](const Range index_var)
{
  return K[index_var];
}


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
