#!/bin/bash

# Initialize the grading variables
correct=0
total=0

function pass () {
  correct=$(($correct + 1))
  echo -e "${GREEN}PASS${NC}"
}

function fail () {
  # Check if an error was passed
  if [ $# -eq 1 ]; then
      echo -e "${RED}FAIL${NC} - $1"
  else
    echo -e "${RED}FAIL${NC}"
  fi
}

# Pass the test name and executable name
# Looks for a test_name.input and a test_name.corr_out
# and uses these files as the sample input and expected output for
# an executable.
# stdin and stdout are used for input and output, respectively (i.e. we're)
# not passing a file via the command line
function diff_test () {
  if [[ -f "$1.input" && -f "$1.corr_out" ]]; then
    # If so, grab the output...
    if timeout 10 $2 < "$1.input" > "$1.test_out"; then
      # ...and diff it against the correct output
      echo "Your program's output is on the left" > "$student_folder/$1.diff"
      if diff "$1.test_out" "$1.corr_out" >> "$student_folder/$1.diff"; then
        pass
        rm "$student_folder/$1.diff"
      else
        fail "Output differs from correct output"
      fi
      rm $1.test_out
    else
      fail "Program failed to execute properly"
    fi
  else
    echo -e "${RED}Input file \"$1.input\" or correct output file \"$1.corr_out\" does not exist${NC}"
    exit 1
  fi
}

# Pass the name of the executable (its path) and an optional file
# Executes a test and marks as passed if returncode is zero
# Should work for both Python and C++ (pass 'python3 test.py' or './a.out')
function execute_test () {
  if [ $# -eq 2 ]; then
    if timeout 10 $1 < $2; then
      pass
    else
      fail "Unit test failed"
    fi
  elif timeout 10 $1; then
    pass
  else
    fail "Unit test failed"
  fi

}

# Just uses the student Makefile to create an executable - assumed to be
# the name of the homework + '.out' (e.g. hw2.out), and runs the diff test
# This is for when we ask for them to implement a driver with specific output
# for a given input
function test_driver () {
  total=$(($total + 1))
  test_dir=$(pwd)
  echo -e "Test: driver..."
  cd $student_folder
  if timeout 10 make; then
    cd $test_dir
    run_test "driver" "$student_folder/$hw_name.out"
  else
    cd $test_dir
    fail "GNU Make was unsuccessful"
  fi
}

# Pass the name of the test and the command-line string to execute it,
# e.g. run_test "diff_test_1" "python3 diff_test_1.py"
function run_test () {
  if [[ -f "$1.args" ]]; then
    local test_args=$(cat "$1.args")
  fi
  # Check if it's a diff test
  if [[ -f "$1.input" && -f "$1.corr_out" ]]; then
    diff_test $1 "$2 $test_args"
  # If it has just an input then we give it the input
  elif [[ -f "$1.input" ]]; then
    execute_test "$2 $test_args" "$1.input"
    # Otherwise just try to execute
  else
    execute_test "$2 $test_args"
  fi
  rm $2
}

# Doesn't need arguments, just used at the end of cpp_main/python_main
# to write test results to file
function test_summary () {
  echo -e "Ran $total tests"
  echo -e "${BLUE}"
  echo -e "Your current score is (out of 100):"
  python3 -c "print(($correct*100)/$total)"
  echo -e "${NC}"
  python3 -c "print(($correct*100)/$total)" > $student_folder/results.txt
  if [ "$correct" -lt "$total" ]; then
    exit 1
  fi
}

function enable_color () {
  # Pretty-printing test results
  RED='\033[0;31m'
  GREEN='\033[0;32m'
  BLUE='\033[0;36m'
  NC='\033[0m'
}

# Pass the folder where student code is, the name of the homework,
# the name of the test header file, and 'true' as fourth argument
# to enable colors (defaults to false)
# (homework name used to determine the name of the executable produced
# by the student Makefile)
function cpp_main () {
  student_folder=$1
  hw_name=$2
  test_header_in=$3
  color_enabled=${4:-false}
  if $color_enabled; then
    enable_color
  fi

  # Our tests
  # Start by making the test header
  test_header=${test_header_in%???} # Remove the .in
  # Check if the function to replace exists,
  if declare -f cpp_replace > /dev/null; then
    cpp_replace $test_header_in $test_header
  else
    # if it doesn't, just copy the file
    cp $test_header_in $test_header
  fi
  exec_name="a.out"
  for test in *.cpp; do
    total=$(($total + 1))
    echo -e "Test: $test..."
    if g++ $test -I$student_folder; then
      run_test $test "./$exec_name"
    else
      fail "Did not compile"
    fi
  done
  rm -f $test_header
  rm -f *.test_out
  test_summary
}
