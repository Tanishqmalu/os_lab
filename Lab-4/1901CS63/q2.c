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
		if(PID > 0)// Creating a fork only for parent
			PID = fork();
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
	
	// exit from the parent process so that the child process becomes orphan
	if(PID>0)exit(0);
	else {
		// Child sleep for 20 seconds
		sleep(20);
		printf("pid = %d\n", getpid());
	} 
	
}