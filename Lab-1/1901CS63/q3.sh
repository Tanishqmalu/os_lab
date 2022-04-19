#!/bin/bash
# Question3

if [ $# -ne 2 ] 
then
    echo "Error: Argument should be of the format [fileName] [numberOfLinesRequired]."

else
    fileName=$1
    numberOfLines=$2
    Current=0
    while read -r line || [ -n "$line" ]
    do
        Current=$(($Current + 1))
    done  < "$fileName"
    
    echo "Number of lines in file: $Current"

    if [ $Current -lt $numberOfLines ]
    then
        echo "Number of lines is less than: $numberOfLines , therefore, deleting the file."
        rm -f $fileName
    fi
fi