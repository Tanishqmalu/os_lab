/* C Program to count the Number of Lines in a Text File */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

//pthread_mutex_t myMutex;
char p;
FILE *fp;
void print(int num) {

    FILE * fPtr;
    char in[100];
    sprintf(in,"%d",num);
    char ex[]=".txt";
    strcat(in,ex);

    fPtr = fopen(in, "w");
    p = fgetc(fp);
	while (p != EOF ) { 
        fputc(p, fPtr);
        //fputc(c,stdout); 
        char ch = p; 
        
        if(ch =='\n'){break;}
        p = fgetc(fp);
    }
	printf("Child %d: I wrote line number: %d !\n", num, num);

}
int main()
{
	char filename[] = "checkLine.c";
	
	
	// Open the file
	fp = fopen(filename, "r");

	// Check if file exists
	if (fp == NULL)
	{
		printf("Could not open file %s", filename);
		return 0;
	}
	char c;
	int count = 0; 
	// Extract characters from file and store in character c
	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n') // Increment count if this character is newline
			count = count + 1;
	// the last line doesn't have \n character
	count++;
	// Close the file
	fclose(fp);
	printf("The file %s has %d lines\n", filename, count);

	int id[count];
	fp = fopen(filename, "r");
	pid_t PID = 1;
	// Let P be the parent process
	for(int i=0;i<count;i++){
		if(PID > 0)
			PID = fork(); // Creating a fork only for parent
		if (PID < 0) fprintf(stderr, "ERROR: ");
				
		char s[100];
		sprintf(s,"%d",i+1);

		/* child process */
		if (PID == 0) { 
			print(i+1);
			exit(0);
	    } else{
	    	wait(0);
	    }

	}
	fclose(fp);
	return 0;
}
