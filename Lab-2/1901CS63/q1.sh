#!/bin/bash
# Problem 1
#Input format: N n1 n2 n3 ..... nn S

# N = Number of elements in the array
# The next N arguments i.e. n1 n2 n3 ... nn will be the elements of the array.
# S = number to be searched
valid=2
valid=$(($valid + $1))
if [ "$#" -ne "$valid" ]
then
    echo "Error: Invalid number of arguments "
    exit 1
fi
 
array=(${@:2:$(($1))})

# Answer Index and number to be searched
answerIndex=-1
searchItem=${!#}

# Seaching for the element in our array
for i in "${!array[@]}";
do
    if [ ${array[$i]} -eq $searchItem ]
    then
        answerIndex=$i
    fi
done

# If valid index is found, print success msg else failure msg
if [ $answerIndex -ne -1 ]
then
    echo "Element S = $searchItem found at index $answerIndex."
else
    echo "Element S = $searchItem not found in our array."
fi