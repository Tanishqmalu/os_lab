##############
## 1901CS63 ##
##############

********************************************************************************************************
Running on Ubunutu environment:

Problem 1:
Run and test using the following commands

sh q1.sh
Output: No arguments passed. Please try again.

sh q1.sh 12 23 23
Output: Too many arguments. Please enter only 1 argument.

sh q1.sh 12008
Output: 80021

sh q1.sh 100
Output: 1

sh q1.sh -289
Output: -982


********************************************************************************************************

Problem 2:
Run and test using the following commands

sh q2.sh
Input:
12
18
Output:
12 13 14 15 16 17 18

sh q2.sh
Input:
15
15
Output:
15

sh q2.sh
Input:
18
15
Output:
Error: First argument should be less than equal to second argument. Try again.


********************************************************************************************************

Problem 3:
Run and test using the following commands

sh q3.sh test.txt
Output: 
Error: Argument should be of the format [fileName] [numberOfLinesRequired].

sh q3.sh test.txt 4
Output:
Number of lines in file: 7

sh q3.sh test.txt 10
Output:
Number of lines in file: 7
Number of lines is less than: 8 , therefore, deleting the file.

********************************************************************************************************

Problem 4:

sh q4.sh 
Input:
Enter directory_path: /home/tanishqmalu/Desktop/test
Enter filename_pattern: uvwx
Enter the new_filename: asd

Therefore the filenames with subsequences uvwx present will be changed to asd_1, asd_2 and so on.


-------------------------------------------------- The End -----------------------------------------------