#!/bin/bash
# Prints a given number in reverse order

if [ $# -eq 0 ]
then
    echo "Error: No arguments passed. Please try again.\n"

elif [ $# -gt 1 ]
then
    echo "Error: Too many arguments. Please enter only 1 argument.\n"

else
    num=$1
    ans=0 
    ii=0
    while [ ${num:$ii:1} -eq 0 && $ii -lt ${#num} ]
 	do    
		ii=$(($ii+1))
	done 
   for (( i=$ii i>-1; i-- )); do
	    ans=$(($ans*10 + ${num:$i:1}))
    done
   echo $ans
fi
