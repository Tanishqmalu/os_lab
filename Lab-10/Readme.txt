To design an MMU

There are 3 functions in the MMU:
1: allocate(process_size): to add a process in the page table
2: translate(logical_address): to translate any logical address to its physical address
3: delete_page(page_no): to delete a specific page with a given page_no.

Input syntax
p v f
a1 a2 a3 a4 .... an a2n 
qi numi
.
.
.
qj numj

(Note: If running on terminal, press ctrl + c to terminate, else if running on any ide simply put in the input as mentioned above.)
Compilation:
g++ q1.cpp -o q1

To run:
./q1
{Input}


Sample Input Output

 -----------------------  -----------------------
			TC1
 -----------------------  -----------------------
7 10 4
0 2 5 7
a 64
t 43
t 241
d 1
a 32

Cannot allocate all the pages, Free frames left = 2 !!

Invalid Page Number

Invalid Page Number

Page does not exists, thus cant delete !!

32 bytes has been alloted to: 3 4 


 -----------------------  -----------------------
			TC2
 -----------------------  -----------------------
7 10 2
0 2 5 7
a 64
d 3
d 5
t 43
a 32
t 26
d 1



64 bytes has been alloted to: 3 4 8 9 10 11 12 13 14 15 16 17 18 19 20 21 

Page number 3 = frame number 9 has been deleted

Page number 5 = frame number 11 has been deleted

The physical address is: 67

32 bytes has been alloted to: 11 9 22 23 24 25 26 27 

The physical address is: 50

Page number 1 = frame number 4 has been deleted
  -----------------------  -----------------------