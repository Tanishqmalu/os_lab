##################
##   1901CS63   ##
## Tanishq Malu ##
##################

## Adding permissions

To add executable permissions to the shell scripts, type the following commands:

sudo chmod a+rx Task1.sh
sudo chmod a+rx Task2.sh


********************************************************************************************************
Problem 1:
********************************************************************************************************

Compile:
gcc q1.c -o q1

Syntax:
./q1 {Number 1} {Number 2}

Sample Input and Output:

--- Case1 ---
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ gcc q1.c -o q1
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ ./q1 2 4

In Child with process ID = 15403 Sum of 2 + 4 = : 6
In Child with process ID = 15404 Multiplication of 2 * 4 = : 8
Division by Parent 15402: 1

--- Case2 ---
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ gcc q1.c -o q1
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ ./q1 10 5

In Child with process ID = 15406 Sum of 10 + 5 = : 15
In Child with process ID = 15407 Multiplication of 10 * 5 = : 50
Division by Parent 15405: 3

********************************************************************************************************
Problem 2:
********************************************************************************************************

Compile:
gcc q2.c -o q2

Syntax:
./q2

Sample Input and Output:

--- Case1 ---
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ gcc q2.c -o q2
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ ./q2
Hello   Hello   Hello   Hello   Hello   Hello   Hello   Hello
   
********************************************************************************************************
Problem 3:
********************************************************************************************************

Compile:
gcc q3.c -o q3

Syntax:
./q3 {Script1_Name ie Name for Task 1} {Task 1 Arguments} {Script2_Name ie Name for Task 2} {Task 2 Arguments}

Sample Input and Output:

--- Case1 ---
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ gcc q3.c -o q3
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ ./q3 Task1.sh 7 88 66 44 55 99 22 33 44 Task2.sh 5
Element S = 44 found at index 2.
The required answer is : 1200

--- Case2 ---
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ gcc q3.c -o q3
tanishqmalu@dell:/mnt/d/Tanishq/lab3$ ./q3 Task1.sh 8 1 2 3 4 5 6 7 8 9 Task2.sh 4

Element S = 9 not found in our array.
The required answer is : 120

-------------------------------------------------- The End -----------------------------------------------