#!/bin/bash
# Problem 2
# Input Format: N

# N = number whos answer needs to be found out

# Recursive function to find the sum of prime numbers less than or equal to a given number
function SumOfPrimeNoLessThan() {
        # Base condition
	if (($1 < 2))
	then
		echo 0
	else
		for((i=2;i<$1;i++))
		do
			if [[ $(($1 % $i)) -eq 0 ]]
			then
                                # It is not a prime number , therefore, recurse for (n-1)
				echo $(SumOfPrimeNoLessThan $(( $1 - 1)) )
				return
			fi
		done
                # It is a Prime number since no nunmber less than it can divide it,  therefore add it
                # and recurse it for (n-1)
		echo $(( $1 + $(SumOfPrimeNoLessThan $(( $1 - 1))) ))
	fi
}

# Recursive function to calculate factorial of a number
function factorial() { 
    # Base Condition
    if (( $1 < 2 ))
    then
        echo 1
    else	
        # Recursive call for (n-1)
        echo $(( $1 * $(factorial $(( $1 - 1 ))) ))
    fi
}

if [ $# -ne 1 ]
then
	echo "Error: Invalid number of arguments."
	exit 1
fi

echo "The required answer is : $(( $(SumOfPrimeNoLessThan $1) * $(factorial $1) ))"
