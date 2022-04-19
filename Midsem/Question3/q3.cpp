#include <bits/stdc++.h>
using namespace std;

// Time quantum of queue
int TQ[] = {4, 3};

// Class to define a single process
class Process {
public:
	int pid;				// Process ID
	int arrivalTime;		// Arrival Time
	int burstlTime;			// Burst Time
	int finishTime;			// Finish Time
	int remainingTime;		// Remaining Time
	int prt;				// Priority
};
/***********************Comparators*******************************/
/* Comparator to sort according to finish times */
bool finishTime_comp(Process p1, Process p2) {
	return p1.finishTime < p2.finishTime;
}

/* Comparator to sort according to arrival times */
bool arrivalTime_comp(Process p1, Process p2) {
	if (p1.arrivalTime != p2.arrivalTime) {
		return p1.arrivalTime < p2.arrivalTime;
	}
	else
		return p1.pid < p2.pid;
		
}
/***********************Comparators*******************************/
/* Updates time and inserts processes which have arrived in ready queue */
void findNextTime(int &time, int updated_time, vector<Process> &process, vector<queue<Process*>> &ready, int &queued) {
	int n = process.size();
	time = updated_time;
	while (time >= process[queued].arrivalTime && queued < n){
		ready[process[queued].prt - 1].push(&process[queued]);
		queued++;
	}
	return;
}
/*****************************************************************/
/* Returns the minimum queue number which is non empty. If all are empty, returns -1 */
int findNextinQueue(vector<queue<Process*>> ready) {
	int queues = ready.size();
	for (int i = 0; i < queues; i++) {
		if (!ready[i].empty()) return i;
	}
	return -1;
}
/*****************************************************************/

// Multi Level Queue Scheduling Algorithm
void multiLevelQueue(vector<Process> &process, int queues) {
	int n = process.size();
	int queued = 0;
	int time = 0;

	// Sort vector according to arrival times
	sort(process.begin(), process.end(), arrivalTime_comp);

	// Ready queue
	vector<queue<Process*>> ready(queues);

	while (true) {
		// If all queues are empty
		if (findNextinQueue(ready) == -1) {
			// If all processes had already arrived, break
			if (queued == n) break;
			// Else update time to nearest arriving process
			findNextTime(time, max(time, process[queued].arrivalTime), process, ready, queued);
		}	

		// Extract first process in queue
		int next_ready = findNextinQueue(ready);
		Process* p = ready[next_ready].front();
		ready[next_ready].pop();

		// Calculate finishTime, remainingTime
		findNextTime(time, time + min(TQ[min(next_ready, 1)], p -> remainingTime), process, ready, queued);
		p -> remainingTime -= min(TQ[min(next_ready, 1)], p -> remainingTime);

		if (p -> remainingTime == 0) p -> finishTime = time;
		else ready[next_ready].push(p);
	} 
	
	return;
}

/* Print average WT and average TAT */
void solve(vector<Process> &process) {
	int n = process.size();
	double avg_wt = 0.0;
	double avg_tat = 0.0;

	for (auto p: process) {
		avg_tat += p.finishTime - p.arrivalTime;			// Add turnaround time TAT = finishTime - arrivalTime
		avg_wt += (p.finishTime - p.arrivalTime) - p.burstlTime; // Add waiting time WT = TAT - burstlTime
	}

	avg_wt /= n;
	avg_tat /= n;
	cout << fixed << setprecision(2);
	cout << "Avg_WT = " << avg_wt << " Avg_TAT = " << avg_tat << endl;

	// Sort vector according to finish times
	sort(process.begin(), process.end(), finishTime_comp);

	for (int i = 0; i < n; i++) {
		cout << "P" << process[i].pid << " ";
	}
	cout << endl;

	return;
}

int main() {
	// Number of processes and time quantum
	int n, q;
	cin >> n >> q;						

	// Vector of processes
	vector<Process> process(n);
	for (int i = 0; i < n; i++) {
		process[i].pid = i + 1;
		cin >> process[i].arrivalTime >> process[i].burstlTime >> process[i].prt;
		process[i].remainingTime = process[i].burstlTime;
	}

	// Find finishTime for all processes
	multiLevelQueue(process, q);
	// Print average WT and average TAT
	solve(process);
}