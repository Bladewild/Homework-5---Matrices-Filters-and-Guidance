/*
* Author: Marky Santos-Tankia
* File: SPLP.hpp Date: 4/3/20
* Class: CS 5201
* Instructor : Clayton Price
*
* implementation file kalman
*/

#include "kalmanfilter.h"

template<typename T>
Kalmanfilter<T>::Kalmanfilter(matrix<T> _A, matrix<T> _B, vector<T> _current_x,
  matrix<T>_P, matrix<T> _R) :
  A(_A), B(_B), current_state_estimate(_current_x),
  current_prob_estimate(_P), R(_R)
{}

template<typename T>
vector<T> Kalmanfilter<T>::operator()(vector<T> state, vector<T> control_vector)
{
  int size;
  ///--- UPDATE
  //control_vector and measurement_matrix need to be updated
  size = state.size();
  matrix<T> meausred_state(matrix<T>::identity(size));
  for (int i = 0; i < size; i++)
  {
    meausred_state(i, i) = state[i];
  }
  //---------------
  //x~i+1=Axi+Bui
  matrix<T> predicted_state_estimate = A * current_state_estimate + B * control_vector;
  //P~i+1=A⋅Pi⋅AT+Q
  matrix<T> predicted_prob_estimate = A * current_prob_estimate * A.transpose();
  matrix<T> Seyeplusone = predicted_prob_estimate + R;
  //CALCULATE K
  //y~i+1=mi+1−V~i+1 error correction noisy state from prediction
  matrix<T> predicted_state_estimate_fixed = matrix<T>::identity(size);
  for (int i = 0; i < size; i++)
  {
    predicted_state_estimate_fixed(i, i) = predicted_state_estimate(i, 0);
  }
  matrix<T> Yhateyeplusone = meausred_state - predicted_state_estimate_fixed;

  //K=P~i+1⋅S−1i+1
  matrix<T> kalman_gain = predicted_prob_estimate * Seyeplusone.invert();

  matrix<T> current_state_estimate_TEMP = predicted_state_estimate_fixed + kalman_gain * Yhateyeplusone;

  //--------------------------
  //measurement_matrix need to be updated
  for (int i = 0; i < size; i++)
  {
    current_state_estimate[i] = current_state_estimate_TEMP(i, i);
  }
  //--------------------------
  current_prob_estimate = (matrix<T>::identity(size) - kalman_gain) * predicted_prob_estimate;
  return current_state_estimate;
}
