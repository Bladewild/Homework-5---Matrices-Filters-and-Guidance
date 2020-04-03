#!/bin/bash

source test_utils.sh

matrix_class=$(cat ../myMatrixName.txt)

# Pass the name of the input and the name of the output file
# Must apply all necessary substitutions on the input file
# and produce the output file
function cpp_replace () {
  sed -e "s/MATRIX_NAME/$matrix_class/g" $1 > $2
}

# Student folder, homework name
student_folder='../'
cpp_main "$student_folder" "hw5" "hw5_grader.h.in"
