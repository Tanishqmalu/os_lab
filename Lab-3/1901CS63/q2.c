#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int func(){
	// In this fork call the Parent process will create a child process = c1
	//      P
	//     / \
	//    c1  P
	fork();
	
	// In this fork call the, let the new child process be c2 and c3 respectively for parents c1 and P
	//       P
	//     /   \
	//    c1    P
	//   / \   / \
	//  c2 c1 c3  P
	fork();
	
	// This Hello gets printed by c1 c2 c3 and p ie. 4 times
	printf("Hello\t");
}
int main() {
	// Let the parent process be denoted by P
	func();
	
	// After returning from function call
	// This Hello gets printed by c1 c2 c3 and p ie. 4 more times
	// Thus Hello gets printed overall 8 times
	printf("Hello\t");
	exit(0);
}