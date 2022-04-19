#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

//Input format: Script1_name N n1 n2 n3 ..... nn S Script2_name n

int main(int argc, char* argv[]) {
	pid_t PID = fork();
	// Parent process
	if (PID > 0) {
		// Putting in required arguments for task 2
		char *argv_task1[3];
		
		argv_task1[0] = argv[argc - 2];
		argv_task1[1] = argv[argc - 1];
		argv_task1[2] = NULL;
		
		char *Script1_name = argv[argc - 2];
		
		// execv(Script_name, arguments)
		execv(Script1_name, argv_task1);
		printf("Error: execv() did not function properly.");
	}
	else {
		// Putting in required arguments for task 2
		char* argv_task2[argc - 2];
		
		argv_task2[0] = argv[1];
		for (int i = 1; i < argc - 3; i++) {
			argv_task2[i] = argv[i + 1];
		}
		argv_task2[argc - 3] = NULL;
		char *Script2_name = argv[1];
		
		// execv(Script_name, arguments)
		execv(Script2_name, argv_task2);
		printf("Error: execv() did not function properly.");
		
	}
	return 0;
}