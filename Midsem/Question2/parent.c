#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char** argv)
{
    int number = argc/2;
    printf("I have %d children.\n", number);
    int arr[number];
	pid_t PID = 1;
	// Let P be the parent process
	int index = 1;
	for(int i=0;i<number;i++){
		if(PID > 0)
			PID = fork(); // Creating a fork only for parent
		if (PID < 0) fprintf(stderr, "ERROR: ");
				
		char s[100];
		sprintf(s,"%d",i+1);
		if(PID==0){
			arr[i] = getpid();
		}
		/* child process */
		if (PID == 0) { 
	
			char *command[] = { "child",s,argv[index],argv[index+1], 0 };
			
			execv(command[0], command);
	        
	        exit(127); /* only if execv fails */
	    }
	    
	    index+=2;
	}
	// After this loop, the parent child tree will look like
	//             P
	//            / \
	//           P  c1
	//          / \
	//         P   c2
	//        / \
	//       P  .......and so on
	
	if(PID>0){
		for(int i=0;i<number;i++){
			wait(&arr[i]);
		}
	}

		printf("All child processes terminated. Parent exits\n");

    return 0;
}