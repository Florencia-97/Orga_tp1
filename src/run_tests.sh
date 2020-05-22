#!/usr/bin/env bash
# ------------------------------------------------------------
#
# Script to test errors in the program arguments.
#
# To remove newlines from a textfile, use
# printf %s "$(cat file)" > file
#
# To print contents of a file, including control characters, do:
# oc -c file
#
# ------------------------------------------------------------

# Program name to test.
PROGRAM_NAME='./conway'

# Failed tests counter.
failedTests=0;

# Colors to be used.
RED="\e[31m";
GREEN="\e[32m";
CYAN="\e[96m";
YELLOW="\e[93m";
BOLD="\033[1m";
DEFAULT="\e[0m";

# Helper and formatting functions definitions.
function header() {
  echo -e "$CYAN------------------------------------------------------$DEFAULT";
  echo -e "$CYAN$1$DEFAULT";
  echo -e "$CYAN------------------------------------------------------$DEFAULT";
}

function msg_true() {
  echo -e "$GREEN\0PASSED \n $DEFAULT PROGRAM OUTPUT:\n\t$1";
}

function msg_false() {
  echo -e "$RED\0FAILED \n $DEFAULT PROGRAM OUTPUT:\n\t$1";
}

function msg_testing() {
  echo -e "Testing: $BOLD$1$DEFAULT";
}

function success_msg() {
  echo -e "  $GREEN$1$DEFAULT";
}

function error_msg() {
  echo -e "  $RED$1$DEFAULT";
}

# ------------------------------------------------------------
# Input parameters tests.
# ------------------------------------------------------------

# Define the expected outputs of each of the test cases with its associated
# test functions.
EXPECTED_OUTPUT_INEXISTENT_INPUT_STREAM=("ERROR: Can't open input stream.")

function test1_parameter_input_inexistent_stream(){
  header "TEST1: inexistent 'input' stream."

	commands=(
  "10 20 20 invalid"
  )

	for i in "${commands[@]}"
	do

		msg_testing "$PROGRAM_NAME $i"

		PROGRAM_OUTPUT=$($PROGRAM_NAME $i 2>&1)

    if [[ "$EXPECTED_OUTPUT_INEXISTENT_INPUT_STREAM" == "$PROGRAM_OUTPUT" ]]; then
      msg_true "$PROGRAM_OUTPUT"
    else
      msg_false "$PROGRAM_OUTPUT"
      failedTests=$(($failedTests+1));
    fi

	done
}

function test11_parameter_output_no_argument(){
  header "TEST11: no 'output' option arg."

	commands=("-o ")

	for i in "${commands[@]}"
	do

		msg_testing "$PROGRAM_NAME $i"

		PROGRAM_OUTPUT=$($PROGRAM_NAME $i 2>&1)

    if [[ "./conway: option requires an argument -- 'o'" == "$PROGRAM_OUTPUT" ]]; then
      msg_true "$PROGRAM_OUTPUT"
    else
      msg_false "$PROGRAM_OUTPUT"
      msg_false "EXPECTED:"
      msg_false "$EXPECTED_OUTPUT_OUTPUT_NO_ARGUMENT"
      failedTests=$(($failedTests+1));
    fi

	done
}

EXPECTED_OUTPUT_OUTPUT_INVALID_STREAM=("ERROR: Invalid output stream.")

function test2_parameter_output_invalid_stream(){
  header "TEST2: invalid 'out' stream."

	commands=(
  "10 20 20 glider -o ."
  "10 20 20 glider -o .."
  "10 20 20 glider -o /"
  "10 20 20 glider -o //"
  )

	for i in "${commands[@]}"
	do

		msg_testing "$PROGRAM_NAME $i"

		PROGRAM_OUTPUT=$($PROGRAM_NAME $i 2>&1)

    if [[ "$EXPECTED_OUTPUT_OUTPUT_INVALID_STREAM" == "$PROGRAM_OUTPUT" ]]; then
      msg_true "$PROGRAM_OUTPUT"
    else
      msg_false "$PROGRAM_OUTPUT"
      failedTests=$(($failedTests+1));
    fi

	done
}

EXPECTED_OUTPUT_OUTPUT_NO_ARGUMENT=("ERROR: not enough input arguments.")

function test21_parameter_output_no_argument(){
  header "TEST21: not enough input arguments."

	commands=("10"
  "10 20"
  "10 20 20")

	for i in "${commands[@]}"
	do

		msg_testing "$PROGRAM_NAME $i"

		PROGRAM_OUTPUT=$($PROGRAM_NAME $i 2>&1)

    if [[ "$EXPECTED_OUTPUT_OUTPUT_NO_ARGUMENT" == "$PROGRAM_OUTPUT" ]]; then
      msg_true "$PROGRAM_OUTPUT"
    else
      msg_false "$PROGRAM_OUTPUT"
      failedTests=$(($failedTests+1));
    fi

	done
}

EXPECTED_OUTPUT_VALID_PARAMETERS=(
"Leyendo estado inicial...
Grabando ../output/glider001.pbm
Grabando ../output/glider002.pbm
Grabando ../output/glider003.pbm
Grabando ../output/glider004.pbm
Grabando ../output/glider005.pbm
Grabando ../output/glider006.pbm
Grabando ../output/glider007.pbm
Grabando ../output/glider008.pbm
Grabando ../output/glider009.pbm
Grabando ../output/glider010.pbm
Listo."
)

function test3_valid_parameters(){
  header "TEST3: all options with correct parameters."

	commands=(
  "10 20 20 glider")

	for i in "${commands[@]}"
	do

		msg_testing "$PROGRAM_NAME $i"

		PROGRAM_OUTPUT=$($PROGRAM_NAME $i 2>&1)


    if [[ "$EXPECTED_OUTPUT_VALID_PARAMETERS" == "$PROGRAM_OUTPUT" ]]; then
      msg_true "$PROGRAM_OUTPUT"
    else
      msg_false "$PROGRAM_OUTPUT"
      failedTests=$(($failedTests+1));
    fi

	done
}
# ------------------------------------------------------------
# Run the tests.
# ------------------------------------------------------------
test1_parameter_input_inexistent_stream
test11_parameter_output_no_argument
test2_parameter_output_invalid_stream
test21_parameter_output_no_argument
test3_valid_parameters

header "Test suite ended."

if [[ $failedTests -eq $zero ]]; then
  success_msg "All tests passed.";
else
  error_msg "Failed tests: $failedTests";
fi
