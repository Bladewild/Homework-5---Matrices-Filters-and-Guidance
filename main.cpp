﻿/*
* Author: Marky Santos-Tankia
* File: main.cpp Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* main file
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "matrix.h"
#include <algorithm>    // std::max
#include "global.h"
#include "model.h"
#include "SPLPFilter.h"
#include "kalmanfilter.h"

using std::cout;
using std::cin;
using std::endl;


void matrixInitializerTest();
void normalModel();
void modelTest();
int main()
{
  
  try
  {
    normalModel();
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
void normalModel()
{
  std::ofstream fout;

  fout.open("dataslnormal.csv");
  double stepsize = 0.1;
  float seconds = 200;
  model modelTesting;

  fout.precision(8); // as requested
  int stepstoTake = seconds / stepsize;
  fout << "Timestep,Alpha,Omega,Theta\n";
  for (int current_step = 0; current_step < stepstoTake; current_step++)
  {
    fout << (current_step / 10.0) << ",";
    modelTesting();
    fout << modelTesting;
    if (current_step == 100)
    {
      modelTesting.controller[5] = 0;
      modelTesting.controller[5] = 0;
      modelTesting.controller[5] = 0;
    }
  }
  fout.close();
}

void modelTest()
{
  std::ofstream fout;
  
  fout.open("dataslpl.csv");
  double stepsize = 0.1;
  float seconds = 200;
  model modelTesting;

  fout.precision(8); // as requested
  int stepstoTake = seconds / stepsize;
  SLPLFilter<double> slplfilter(vector<double>{0, 0, 0}, 0.1, 10);
  fout << "Timestep,Alpha,Omega,Theta\n";
  for (int current_step = 0; current_step < stepstoTake; current_step++)
  {
    fout << (current_step/10.0) << ",";
    modelTesting();
    modelTesting.altfilterNoise(slplfilter);
    fout << modelTesting;
  }
  fout.close();
  //-----------------------

  fout.open("datakalman.csv");
  stepsize = 0.1;
  seconds = 200;
  model modelTesting2;

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
    {0.0,0.0,0.1* 4.0 / 100000.0},//omega
    {0.0,0.0,4.0/100000.0},//alpha
  };

  vector<double> initial_state = {0, 0, 0};

  matrix<double> P =
  {
    {1.0,0.0,0.0},//theta
    {0.0,1.0,0.0},//omega
    {0.0,0.0,1.0},//alpha
  };

  matrix<double> R =
  {
    {0.2,0.0,0.0},//theta
    {0.0,0.2,0.0},//omega
    {0.0,0.0,0.2},//alpha
  };

  Kalmanfilter<double> f(A, B, initial_state, P, R, modelTesting2.controller);
  fout.precision(8); // as requested
  stepstoTake = seconds / stepsize;
  fout << "Timestep,Alpha,Omega,Theta\n";
  for (int current_step = 0; current_step < stepstoTake; current_step++)
  {
    fout << (current_step / 10.0) << ",";
    modelTesting2();
    modelTesting2.altfilterNoise(f);
    fout << modelTesting2;
    //cout << modelTesting2;
  }
  fout.close();
}

void matrixInitializerTest()
{
  matrix<int> m { {1,2,3,4},{5,6,7,8} };
  matrix<int> m2{ {1,1,1,1},{1,1,1,1} };
  matrix<int> m3{ {5,5},{6,6} };
  matrix<int> copy(m);
  matrix<int> assign = copy;
  cout << "copy:\n"<<copy << endl;
  cout << "assign:\n" << assign << endl;
  matrix<int> subtract = m - m2;
  matrix<int> addition = m + m2;
  cout << "\nsubtract:\n"<<subtract << endl << endl;;
  cout << "addition:\n"<<addition << endl << endl;;
  matrix<int> scalarLeft = 2 * m2;
  matrix<int> scalartRight = m2 * 3;
  cout << "scalarLeft:\n"<<scalarLeft << endl;
  cout << "scalartRight:\n" << scalartRight << endl;


  matrix<int> left{ {2,4},{6,3},{1,2} };
  matrix<int> right{ {3,4,1},{3,3,8}};
  //matrix<int> left{ {1,2,3},{4,5,6} };
  //matrix<int> right{ {7,8},{9,10},{11,12} };
  cout << left << endl;
  cout << right << endl;
  matrix<int> multiplication = left * right;
  cout << "multiplication:\n"<<multiplication << endl;
  matrix<int> unary = -m2;
  cout << "unary:\n"<<unary << endl;


  matrix<int> FA{ {1,1},{2,2},{3,3} };
  cout << "FA\n"<<FA << endl<<endl;
  cout << "FA transpose:\n"<<FA.transpose() << endl;
  double test = static_cast<double>(FA);
  cout << test << endl<< endl<< endl;
  //matrix<double> inverse{ {3,0,2},{2,0,-2},{0,1,1} };
  matrix<double> inverse{ {1.2, 9}, { 0, 1 } };
  cout<<inverse.invert()<<endl;

  matrix<int> Ident{ {1,2,0},{0,1,2},{0,0,1} };
  vector<int> v{ 0,0,2 };
  cout << "M*v\n" << (Ident*v) << endl << endl;


  matrix<double> A =
  {
    {1.0,0.1,0.0},//theta
    {0.0,1.0,0.1},//omega
    {0.0,0.0,0.0},//alpha
  };

  matrix<double> B =
  {
    {1.0,0.1,0.0}
  };
  vector<double> d{ 5,5,5 };
  //vector<double> d{ 0.0065850289,0.0028314586,0.014294247 };
  cout << "M*v22\n" << (A * d) << endl << endl;
  cout << "M*v33\n" << (d * B) << endl << endl;
  //0.0014294247
  string temp_input =
    "1 2 3\n4 5 6\n7 8 9\n";
  std::istringstream tokenStream(temp_input);
  matrix<int> finMatrixtest;
  cin >> finMatrixtest;
  cout << "\n\n\nfinMatrixtest\n" << finMatrixtest << endl;

}

