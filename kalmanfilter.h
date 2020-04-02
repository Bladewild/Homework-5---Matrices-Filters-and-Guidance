/*
* Author: Marky Santos-Tankia
* File: .h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
*
*/
/*! \file
 *
 *
 */
#ifndef KALMANTFILTER_H
#define KALMANTFILTER_H

#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "basefilter.h"
#include "PID.h"

 /*
 * Class:
 */

template<typename T>
class Kalmanfilter : public BaseFilter<T>
{
private:
  matrix<T> A;
  matrix<T> B;
  vector<T> current_state_estimate; // Initial state estimate.
  matrix<T> current_prob_estimate; //Initial covariance estimate.
  matrix<T> R; //Estimated error in measurements.
  vector<T> control_vector;
  PID& modelController;

public:
  Kalmanfilter<T>(matrix<T> _A, matrix<T> _B, vector<T> _current_x,
    matrix<T>_P, matrix<T> _R, PID& _Pcontrol) : 
    A(_A),B(_B),current_state_estimate (_current_x),
    current_prob_estimate(_P),R(_R),
    modelController(_Pcontrol)
  {}
  virtual vector<T> operator()(vector<T> state)
  {
    //cout << "---------STATE---------" << endl;
    //cout << state[0] << endl;
    //cout << state[1] << endl;
    //cout << state[2] << endl;
    //cout << "---------STATE---------" << endl;
    //cout << "FILTER3\n";
    int size = state.size();
    update();
    matrix<T> meausred_state = convertVector(state);
    //#---------------------------Prediction step-----------------------------
    //x~i+1=Axi+Bui
    matrix<T> one = A * current_state_estimate;
    matrix<T> two = B * control_vector;
    matrix<T> predicted_state_estimate = one + two ;
    //std::cout << "-----------------\n" << std::endl;
    //std::cout << "A\n" << A << std::endl;
    //std::cout << "current_state_estimate\n" << current_state_estimate << std::endl << std::endl;
    //std::cout << "B\n" << B << std::endl;
    //std::cout << "control_vector\n" << control_vector << std::endl << std::endl;
    //std::cout << "one\n" << one << std::endl << std::endl;
    //std::cout << "two\n" << two << std::endl << std::endl;
    //std::cout << "STATEMATRIX\n" << predicted_state_estimate << std::endl << std::endl;
    //std::cout << "-----------------\n"<< std::endl <<std::endl;

    //P~i+1=A⋅Pi⋅AT+Q
    matrix<T> predicted_prob_estimate = A * current_prob_estimate * A.transpose();

    //std::cout << "-----------------\n" << std::endl;
    //std::cout << "predicted_state_estimate_fixed\n" << predicted_state_estimate_fixed << std::endl;
    //std::cout << "state_matrix\n" << state_matrix << std::endl;
    //std::cout << "innovation\n" << innovation << std::endl << std::endl;
    //std::cout << "-----------------\n" << std::endl << std::endl;
    //Si+1=P~i+1+R
    matrix<T> Seyeplusone = predicted_prob_estimate + R;

    //std::cout << "-----------------\n" << std::endl;
    //std::cout << "A\n" << A << std::endl;
    //std::cout << "A.transpose()\n" << A.transpose() << std::endl;
    //std::cout << "current_prob_estimate\n" << current_prob_estimate << std::endl;
    //std::cout << "predicted_prob_estimate\n" << predicted_prob_estimate << std::endl << std::endl;
    //std::cout << "-----------------\n" << std::endl << std::endl;

    //CALCULATE K
    //#--------------------------Observation step-----------------------------
    //y~i+1=mi+1−V~i+1 error correction noisy state from prediction

    matrix<T> predicted_state_estimate_fixed = matrix<T>::identity(size);
    for (int i = 0; i < size; i++)
    {
      predicted_state_estimate_fixed(i, i) = predicted_state_estimate(i,0);
    }


    matrix<T> Yhateyeplusone = meausred_state - predicted_state_estimate_fixed;



    //std::cout << "-----------------\n" << std::endl;
    //std::cout << "R\n" << R << std::endl;
    //std::cout << "predicted_prob_estimate\n" << predicted_prob_estimate << std::endl;
    //std::cout << "innovation_covariance\n" << innovation_covariance << std::endl << std::endl;
    //std::cout << "-----------------\n" << std::endl << std::endl;
    //#-----------------------------Update step-------------------------------
    //K=P~i+1⋅S−1i+1
    matrix<T> kalman_gain = predicted_prob_estimate * Seyeplusone.invert();

    //std::cout << "-----------------\n" << std::endl;
    //std::cout << "innovation_covariance.invert()\n" << innovation_covariance.invert() << std::endl;
    //std::cout << "predicted_prob_estimate\n" << predicted_prob_estimate << std::endl;
    //std::cout << "kalman_gain\n" << kalman_gain << std::endl << std::endl;
    //std::cout << "-----------------\n" << std::endl << std::endl;

    matrix<T> current_state_estimate_TEMP = predicted_state_estimate_fixed + kalman_gain * Yhateyeplusone;
    current_state_estimate = convertMatrix(current_state_estimate_TEMP);
    //# We need the size of the matrix so we can make an identity matrix.

    //# eye(n) = nxn identity matrix.
    current_prob_estimate = (matrix<T>::identity(size) - kalman_gain) * predicted_prob_estimate;
    //cout<<"alpha%:"
    return current_state_estimate;
  }

  virtual matrix<T> convertVector(vector<T> state)
  {
    //control_vector and measurement_matrix need to be updated
    int size = state.size();
    matrix<T> temp(matrix<T>::identity(size));
    for (int i = 0; i < size; i++)
    {
      temp(i,i) = state[i];
    }
    return temp;
  }
  virtual vector<T> convertMatrix(matrix<T> state)
  {
    //control_vector and measurement_matrix need to be updated
    int size = state.rows();
    vector<T> temp(size);
    for (int i = 0; i < size; i++)
    {
      temp[i] = state(i,i);
    }
    return temp;
  }
  virtual void update()
  {
    //control_vector and measurement_matrix need to be updated
    vector<T> temp(B.rows());
    for (int i = 0; i < temp.size();i++)
    {
      temp[i] = 0;
    }
    temp[temp.size() - 1] = modelController.getU();
    //std::cout << "U: "<<modelController.getU() << std::endl;
    control_vector = temp;

    return;
  }
};


#endif
