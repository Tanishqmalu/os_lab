#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <ctype.h> 

int main(){
	int n;
	scanf("%d",&n);
	pid_t PID = 1;
	// Let P be the parent process
	for(int i=0;i<n;i++){
		if(PID > 0)
			PID = fork(); // Creating a fork only for parent
		if (PID < 0) fprintf(stderr, "ERROR: ");

	}
	// After this loop, the parent child tree will look like
	//             P
	//            / \
	//           P  c1
	//          / \
	//         P   c2
	//        / \
	//       P  .......and so on
	
	// exit from the child process before the parent process completes to make it a zombie process
	if(PID==0)exit(0); 
	else {
		// Parent process sleeps for 20 sec		
		sleep(20);
		printf("Parent pid = %d\n", getpid());
	} 
	
}