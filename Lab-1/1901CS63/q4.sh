#!/bin/bash
# Question4

echo -n "Enter directory_path: "
read directory
echo -n "Enter filename_pattern: "
read pattern
echo -n "Enter the new_filename: "
read newFileName

cd $directory

fileNum=1

for file in *
do
    X=0
    fileName="$(basename -- "$file")"
    fileExtension="${fileName##*.}"
    for ((i=0; i < ${#fileName} && X < ${#pattern}; i++))
    do
        if [ "${fileName:$i:1}" == ${pattern:$X:1} ]
        then
            X=$(($X + 1))
        fi
    done
    if [ $X -eq ${#pattern} ]
    then
        newName=${newFileName}_${fileNum}.${fileExtension}
        $(mv $file $newName)
        ((fileNum++))
    fi
done