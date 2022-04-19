#!/bin/bash
# Q2 Prints all the Number in a given range


read A
read B
if [ $A -gt $B ]
then
    echo "Error: First argument should be less than equal to second argument. Try again."

else 
    while [ $A -le $B ]
    do
        echo -n "$A "
        A=$(($A + 1)) 
    done
    echo ""
fi
