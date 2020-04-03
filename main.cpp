/*
* Author: Marky Santos-Tankia
* File: main.cpp Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* main file
*/
#include <iostream>
#include <sstream>
#include <string>
#include "matrix.h"
#include <algorithm>    // std::max
#include "global.h"
#include "model.h"
#include "SPLPFilter.h"
#include "kalmanfilter.h"
#include "combinationfilter.h"
#include "dummyfilter.h"
#include <array>

using std::cout;
using std::cin;
using std::endl;

void matrixInitializerTest();
void modelTest();
void driver();
int main()
{
  
  try
  {
    driver();
    //modelTest();
    //matrixInitializerTest();
  }
  catch (const std::out_of_range & oor) {
    std::cerr << "\nOut of Range error: " << oor.what() << '\n';
  }
  catch (const std::invalid_argument & ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  catch (const std::length_error & le) {
    std::cerr << "Length error: " << le.what() << '\n';
  }
  catch (const std::domain_error & de) {
    std::cerr << "Domain error: " << de.what() << '\n';
  }
  catch (...)
  {
    std::cerr << "An uknown error has occured." << '\n';
  }

  return 0;
}
void driver()
{
  double R = 4;
  double I = 100000;
  vector<double> state{ 0, 0, 0 };
  double desiredtheta = 3.14159265358979323846 / 8;
  vector<double>Kinput{ 4000, 100, 6000 };
  double stepsize = 0.1;
  float seconds = 200;
  int stepstoTake = seconds / stepsize;
  double h = stepsize;


  matrix<double> A =
  {
    {1.0,h  ,0.0},//theta
    {0.0,1.0,h  },//omega
    {0.0,0.0,0.0},//alpha
  };

  matrix<double> B =
  {
    {0.0,0.0,0.01 * 4.0 / 100000.0},//theta
    {0.0,0.0,0.1 * 4.0 / 100000.0},//omega
    {0.0,0.0,4.0 / 100000.0},//alpha
  };

  vector<double> initial_state = { 0, 0, 0 };

  matrix<double> P =
  {
    {1.0,0.0,0.0},//theta
    {0.0,1.0,0.0},//omega
    {0.0,0.0,1.0},//alpha
  };

  matrix<double> R_Error =
  {
    {0.2,0.0,0.0},//theta
    {0.0,0.2,0.0},//omega
    {0.0,0.0,0.2},//alpha
  };



  DummyFilter<double> dummyfilter;
  SLPLFilter<double> slplfilter(vector<double>{0, 0, 0}, 0.1, 10);
  Kalmanfilter<double> kfilter(A, B, initial_state, P, R_Error);
  //----

  SLPLFilter<double> slpl2filter(vector<double>{0, 0, 0}, 0.1, 10);
  Kalmanfilter<double> k2filter(A, B, initial_state, P, R_Error);
  CombinationFilter<double> combinationfilter{ &slpl2filter,&k2filter };

  model MODEL_DUMMY(stepsize, R, I, desiredtheta,
    state, Kinput);
  model MODEL_SLPL(stepsize, R, I, desiredtheta,
    state, Kinput);
  model MODEL_KALMAN(stepsize, R, I, desiredtheta,
    state, Kinput);
  model MODEL_COMBINATION(stepsize, R, I, desiredtheta,
    state, Kinput);

  cout.precision(8); // as requested
  for (int current_step = 0; current_step < stepstoTake; current_step++)
  {
    MODEL_DUMMY();
    MODEL_DUMMY.addNoise();
    MODEL_DUMMY.filterNoise(dummyfilter);
    //----
    MODEL_SLPL();
    MODEL_SLPL.addNoise();
    MODEL_SLPL.filterNoise(slplfilter);
    //----
    MODEL_KALMAN();
    MODEL_KALMAN.addNoise();
    MODEL_KALMAN.filterNoise(kfilter);
    //----
    MODEL_COMBINATION();
    MODEL_COMBINATION.addNoise();
    MODEL_COMBINATION.filterNoise(combinationfilter);
    cout << MODEL_DUMMY.getTheta() <<" "<< MODEL_SLPL.getTheta()<<" "
      <<MODEL_KALMAN.getTheta()<<" "<<MODEL_COMBINATION.getTheta()<<"\n";
  }
}