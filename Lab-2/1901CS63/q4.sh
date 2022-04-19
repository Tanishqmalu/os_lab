#!/bin/bash
# Problem 4
# Input Format: Password string (within inverted commas "")

if [ $# -ne 1 ]; 
then
	echo "Error: Invalid number of arguments."
	exit 1
fi

# Storing password and length
password=$1
length=${#password}
echo "Your Password: $1"
echo "Length of your Password: $length"
echo ""

# Password must contain the following
alphabets="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
numbers="0123456789"
specialCharacters="/()<>?"

# A Function which check the presence of the characters required for a valid password
function checkValid() {
	# $1 is basically the set of characters whose presence is to be checked
	charactersRequired=$1
	for ((i = 0; i < $length; i++))
    	do
		for ((j = 0; j < ${#charactersRequired}; j++))
        	do
			if [ ${password:i:1} == ${charactersRequired:j:1} ]; 
			then
				echo 1
				return
			fi
		done
	done
	echo 0
    return					
}

# Checking our requirements of valid password

alphabetsValid=$(checkValid "$alphabets")
numbersValid=$(checkValid "$numbers")
specialCharactersValid=$(checkValid "$specialCharacters")

if [ $length -ge 7 ] && [ $alphabetsValid -eq 1 ]  && [ $numbersValid -eq 1 ] && [ $specialCharactersValid -eq 1 ]; then
	echo "<Valid Password>"
else
	echo "<Invalid Password>"
	if [ $length -ge 7 ]; then
		echo "Length is ok"
	else
		echo "Length is less than 7."
	fi
	if [ $alphabetsValid -eq 1 ]; then
		echo "Alphabets is/are present"
	else
		echo "Alphabets not present."
	fi
	if [ $numbersValid -eq 1 ]; then
		echo "Numbers is/are present."
	else
		echo "Numbers not present."
	fi
	if [ $specialCharactersValid -eq 1 ]; then
		echo "specialCharacters is/are present."
	else
		echo "specialCharactersValid not present."
	fi
fi
