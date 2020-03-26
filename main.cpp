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
#include <fstream>
#include "global.h"

using std::cout;
using std::cin;
using std::endl;


void matrixInitializerTest();
int main()
{
  
  try
  {
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
  double test = static_cast<double>(FA);
  cout << test << endl<< endl<< endl;
  //matrix<double> inverse{ {3,0,2},{2,0,-2},{0,1,1} };
  matrix<double> inverse{ {1.2, 9}, { 0, 1 } };
  cout<<inverse.invert()<<endl;
  //newtonRaphsond(8);
  //newtonRaphsonf(8);
}

