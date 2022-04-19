#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
	
    int n; scanf("%d",&n);


    // Let Parent process = P
    pid_t PID = fork();
	//      P
	//     / \
	//    c1  P
	
	// if pid<0 means forking has failed
    if (PID < 0)fprintf(stderr, "Error: fork error");  
    if (PID > 0) {
    	wait(0); // wait till the child process completes
    } 
    else {
		// c1 reaches here
		//      P
		//     / \
		//    c1  P
		//   /  \
		// Print Generate
		
		// array to stor lucas numbers
		long long int arr[n];
		for (int i = 0; i < n; i++) {
			arr[i] = 0;
		}
		// File descriptor for piping/ communication between two childs
		int FD[2];
		if (pipe(FD) == -1) {
			return -1;
		}
    	PID = fork();
    	
    	// if pid<0 means forking has failed
    	if (PID < 0) {
    		fprintf(stderr, "Error: fork error");
    	}
    	
    	// Printing lucas number via Child 1
    	if (PID > 0) {
    		wait(0);
    		printf("printing lucas number, pid = %d\n", getpid());
    		
    		// reading from child 1
    		read(FD[0], arr, sizeof(long long int) * n);
    		
    		for(int i=0;i<n;i++){
    			printf("%lld ",arr[i]);
    		}
    		printf("\n");
    	}
    	// Genrating lucas number Child 2
    	else {
    		printf("Generating lucas number, pid = %d\n", getpid());
    		
    		// Algorithm to generate lucas number
    		int a=2,b=1,c;
    		int i=0;
   
			for(; i<n;)
			{
				arr[i++]=a;
				c=a+b;
				a=b;
				b=c;
			}
    		// communicating back to parent process
    		write(FD[1],&arr, sizeof(long long int)*n);
    	}
    }
    return 0;
}