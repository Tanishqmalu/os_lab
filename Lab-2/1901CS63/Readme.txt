##################
##   1901CS63   ##
## Tanishq Malu ##
##################

## Adding permissions

To add executable permissions to the shell scripts, type the following commands:

sudo chmod a+rx q1.sh
sudo chmod a+rx q2.sh
sudo chmod a+rx q3.sh
sudo chmod a+rx q4.sh

********************************************************************************************************

Problem 1:
Syntax:
./q1.sh {N = Number of elements in the array} {(n1 n2 n3.... nn) = array elements, space separated} {S = Number to be searched}

Sample Input and Output: 

## If we try to give invalid number of inputs, it gives an error
tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q1.sh 5 1 2 3 4 5 6 7
Error: Invalid number of arguments

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q1.sh 2 2 3 5
Element S = 5 not found in our array.

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q1.sh 3 8 4 5 5
Element S = 5 found at index 2.

********************************************************************************************************

Problem 2:
Syntax:
./q2.sh {N = Input number}

Sample Input and Output: 

## If we try to give invalid number of inputs, it gives an error
tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q2.sh 7 5
Error: Invalid number of arguments.

## factorial(5) = 120, sum of primeno less than equal to(5) = 10, therefore answer = 120*10 = 1200
tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q2.sh 5
The required answer is : 1200

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q2.sh 6
The required answer is : 7200

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q2.sh 7
The required answer is : 85680
********************************************************************************************************

Problem 3:
Sybtax:
./q3.sh {num1 = Input Number 1} { num2 = Input number 2}

Sample Input and Output: 

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q3.sh 154 202
Xor of 154 and 202 = 80

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e/1901CS63$ ./q3.sh 441 190
Xor of 441 and 190 = 263

## Time Analysis 

## Shell Program
tanishqmalu@DESKTOP-5JCAMRU:/mnt/e/1901CS63$ ./q3.sh 500 785
Xor of 500 and 785 = 741

real    0m0.018s
user    0m0.000s
sys     0m0.016s

## C Program
gcc q3.c
time ./q3 500 785
Xor of 500 and 785 = 741

real    0m0.003s
user    0m0.002s
sys     0m0.000s

********************************************************************************************************

Problem 4:
Syntax:
./q4.sh {Password string (within inverted commas)} 

Sample Input and Output: 

tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q4.sh "hello45d"
Your Password: hello45d
Length of your Password: 8

<Invalid Password>
Length is ok
Alphabets is/are present
Numbers is/are present.
specialCharactersValid not present.



tanishqmalu@DESKTOP-5JCAMRU:/mnt/e$ ./q4.sh "hello45d("
Your Password: hello45d(
Length of your Password: 9

<Valid Password>


-------------------------------------------------- The End -----------------------------------------------