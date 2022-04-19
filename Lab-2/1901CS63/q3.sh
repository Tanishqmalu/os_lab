#!/bin/bash
# Problem 3
# Input format: num1 num2

# num1 = Input number 1
# num2 = Input number 2

# Function to find and print XOR value
function xor() {
    num1=$1
    num2=$2
    result=0
    power=1

    # Take the numbers bit by bit
    while [[ num1 -gt 0 ]] || [[ num2 -gt 0 ]]
    do
        num1_bin=$(($num1 % 2))
        num2_bin=$(($num2 % 2))
	
	# A XOR B = (((NOT)A)*B) + (A*((NOT)B))
        xorOfLSB=$(($num1_bin * !$num2_bin + !$num1_bin * $num2_bin))
        
        # Update the result
        result=$(($result + $xorOfLSB * $power))
	
	# right shift of both the numbers
        num1=$(($num1 / 2))
        num2=$(($num2 / 2))

        power=$(($power * 2))
    done
    echo "$result"
}
if [[ $# -ne 2 ]]
then
    echo "Error: Invalid number of arguments."
    exit 1
else
    echo "Xor of $1 and $2 = $(xor $1 $2) "
fi
