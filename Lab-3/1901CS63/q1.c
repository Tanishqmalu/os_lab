#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 

// Forking fails
void Fork_Fail() {
	printf("ERROR: Fork failed.");
    exit(0);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Invalid number of arguments. \n");
		return 0;
	}

    int a, b;
    sscanf(argv[1], "%d", &a);
    sscanf(argv[2], "%d", &b);

	// Setting up the pipe for communication with Child 1
    int FD1[2]; 

    // Setting up the pipe for communication with Child 2
    int FD2[2];

    if (pipe(FD1) == -1 || pipe(FD2) == -1) {
    	printf("ERROR: Pipe did not set up successfully.");
    	exit(0);
    }
    // Let Parent process = P
    pid_t PID = fork();
	//      P
	//     / \
	//    c1  P
	
	// if pid<0 means forking has failed
    if (PID < 0) Fork_Fail();

   
    if (PID > 0) {
    	// P reaches here
    	int sum, product;
    	// Result of child1
    	read(FD1[0], &sum, sizeof(int));
    	
    	// Result of child 2
    	read(FD2[0], &product, sizeof(int));
    	
    	printf("Division by Parent %d: %d\n", getpid(), (product / sum));
    } 
    else {
		// c1 reaches here
		//      P
		//     / \
		//    c1  P
		//   /  \
		// sum  multiply
    	PID = fork();
    	
    	// if pid<0 means forking has failed
    	if (PID < 0) {
    		Fork_Fail();
    	}
    	
    	// Sum Child 1
    	if (PID > 0) {
    		int ans = a + b;
    		printf("In Child with process ID = %d Sum of %d + %d = : %d\n", getpid(), a, b, ans);
    		
    		// communicating back to parent process
    		write(FD1[1], &ans, sizeof(int));
    	}
    	// Multiply Child
    	else {
    		int ans = a * b;
    		printf("In Child with process ID = %d Multiplication of %d * %d = : %d\n", getpid(), a, b, ans);
    		
    		// communicating back to parent process
    		write(FD2[1], &ans, sizeof(int));
    	}
    }
    return 0;
}