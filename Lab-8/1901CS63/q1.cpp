#include <bits/stdc++.h>
using namespace std;
int n,m;

// Lets assume maximum number of processes & resources to be 200 

int available[200];			// Available resources
int allocated[200][200];	// Currently allocated resources to the processes
int MAX[200][200];			// Maximum resources required by the processes
int need[200][200];			// It indicates the remaining number of resources required
int safe[200];				// An array to store a safe sequence
bool Completed[200];		//an array to find process which have beem executed or not currently

int total = 0;				// Total safe-sequences
int Curr_size;				// Size of a building safe sequence

// Function to print a sequence
void printSequence() {
	total+=1;
	cout<<"Safe sequence "<<total<<": ";
	for (int i = 0; i < n; i++) {
		cout<<safe[i];
		if (i != (n - 1))
			cout<<" -> ";			
	}
	cout<<endl;
}

// Function to add resources from allocated[proces_index] to available
void Update_resources_add(int process_index) {
	for (int i = 0; i < m; i++) {
		available[i] += allocated[process_index][i];
	}
	return;
}

// Function to subtract resources from allocated[proces_index] to available
void update_resources_subtract(int process_index) {
	for (int i = 0; i < m; i++) {
		available[i] -= allocated[process_index][i];
	}
	return;
}

// function to check if process can be allocated or not
bool can_process(int process_index) {
	bool flag = true;
	// check if all the available resources are greater than 
	// need of process, then process can be executed
	for (int i = 0; i < m; i++) {
		if (need[process_index][i] > available[i])
			flag = false;
	}
	return flag;
}



/* Find and print all the safe-sequences using Banker's Algorithm */
void find_safe_sequence() {
	// Base case
	// If a safe-sequence is found, display it
	if (Curr_size == n){
		 printSequence();
		 return;
	}
	
	for (int i = 0; i < n; i++) {
		// If process is not Completed already and can be allocated the resources
		if (Completed[i] == false && can_process(i)) {
			Completed[i] = true;
			// Once the current process gets completed, its resources gets freed
			// Thus, we can add these resources into available resources
			// i.e. available[j] += allocated[curr][j]
			Update_resources_add(i);
			// Find remaining safe sequence by taking process i at position Curr_size
			safe[Curr_size++] = i;
			find_safe_sequence();
			// Remove i from safe sequence to make space for other combinations
			Curr_size--;
			Completed[i] = false;
			update_resources_subtract(i); // available -= allocated[i] vector
		}
	}
	
}

int main() {

	cout<<"Enter the no of process: ";
	cin>>n;
	cout<<"Enter the no of resources: ";
	cin>>m;
	
	// Input available resources
	cout<<"Enter the available resources: "<<endl;
	for (int i = 0; i < m; i++) {
		cin>>available[i];
	}
	
	// Input allocation matrix	
	cout<<"Enter the allocation matrix: "<<endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin>>allocated[i][j];
		}
	}
	// Input MAX matrix	
	cout<<"Enter the MAX matrix: "<<endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin>>MAX[i][j];
		}
	}
	
	// Finding need matrix
	// need[i][j] = MAX[i][j] - allocated[i][j];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = MAX[i][j] - allocated[i][j];
		}
	}
	
	// Initialising Completed matrix to false
	memset(Completed, false, sizeof(Completed));
	
	// Find asafe sequences
	find_safe_sequence();
	
	// If total ==0 no safe sequence exists
	if (total == 0) cout<<endl<<"There are no safe-sequences!"<<endl;
	
	return 0;
}