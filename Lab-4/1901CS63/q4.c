#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <ctype.h>    



int main(int argc, char * argv[]) {   
    if (argc != 3){
        printf("Invalid number of arguments\n");
        return 1;
    }
    
    fflush(stdout);
    
    // Parent Process
    if (fork() > 0) {
    	
    	// Waiting for that child process to complete since we cant display file2 without copying from file1   
        wait(0)  ;

        fflush(stdout);
        
        // After first child completes its task, create child 2 which displays file2.
        if (fork() > 0) { 
	        
            wait(0); // Waiting for child 2 to print the content of file2  

            fflush(stdout);
            
            // Third child process: Deletes file 2
            if (fork() == 0) { 
                printf("\nTask3: I will delete file 2. My PID: %d\n", getpid());
                remove(argv[2]);
                
            }
            else {
                wait(0);
                printf("\nParent PID:: %d\n\n", getpid());
            }

        }
        // Second Child Process: Display new content of file 2
        else {
            printf("\nTask2: I will print the new content of file f2. My PID: %d\n", getpid());
            
            printf("\n--FILE 2--\n");
            FILE *file2;              // To read file2 to print itd content
            file2 = fopen(argv[2], "r");
            char c = fgetc(file2);
            while(c != EOF) {
                fputc(c, stdout); // print the received word to the file
                c = fgetc(file2);
            }
            printf("\n\n");
            fclose(file2);            // CLose file pointer
        }
    }
    // First child: Copy contents of file1 to file2
    else {
        printf("\nTask1: I will copy file f1 to another file f2. My PID: %d\n", getpid());
        FILE *file1;
        FILE *file2;
        
        // Copying file1 into file 2
        file1 = fopen(argv[1], "r");
        file2 = fopen(argv[2], "w");
        char c = fgetc(file1); 
        while (c != EOF) { 
            fputc(c, file2); 
            c = fgetc(file1); 
        }
        
        fclose(file1);// CLose file pointer
        fclose(file2);// CLose file pointer
    }
    return 0;
}