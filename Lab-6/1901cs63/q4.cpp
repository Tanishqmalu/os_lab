#include <bits/stdc++.h>
#define TIME_QUANTUM 1
using namespace std;

// A class of a single process
class Process {
public:
	int pid;				// Process ID
	int arr_time;			// Arrival Time
	int burst_time;			// Burst Time
	int wait_time;			// Waiting Time
	int fin_time;			// Finish Time
	int turn_around_time;	// Turn Around Time
	int remain_time;		// Remaining Time
};

// sort according to arrival time
bool arr_time_comp(Process p1, Process p2) {
	if (p1.arr_time == p2.arr_time) 
		return (p1.pid) < (p2.pid);
	else
		return (p1.arr_time) < (p2.arr_time);
}

// sort according to finish time
bool ft_comp(Process p1, Process p2) {
	return (p1.fin_time) < (p2.fin_time);
}

// sort according to burst time
struct compareRemainingTime {
	bool operator()(Process* p1, Process* p2) {
		if ((p1 -> remain_time) == (p2 -> remain_time))
			return (p1 -> pid) > (p2 -> pid);
		else
			return (p1 -> remain_time) < (p2 -> remain_time);
	}
};

// Longest Remaining Time First Algorithm
void solve(vector<Process> &process) {
	int n = process.size();
	int queued = 0;
	int time = 0;

	// Sort vector according to arrival times
	sort(process.begin(), process.end(), arr_time_comp);

	priority_queue<Process*, vector<Process*>, compareRemainingTime> q;

	while (true) {
		// If all finished, break
		if (q.empty() && queued == n) break;

		// If queue is empty, increase time
		if (q.empty()) time = max(time, process[queued].arr_time);

		// Push all processes whose arrival time <= time
		while (time >= process[queued].arr_time && queued < n){
			q.push(&process[queued]);
			queued++;
		}
		
		// Extract shortest remaining burst time process
		Process* p = q.top();
		q.pop();

		// Calculate WT, FT, TAT, RT (Update BT), LET
		time += min(TIME_QUANTUM, p -> remain_time);
		p -> remain_time -= min(TIME_QUANTUM, p -> remain_time);
		if (p -> remain_time == 0) {
			p -> fin_time = time;
			p -> turn_around_time = p -> fin_time - p -> arr_time; 
			p -> wait_time = p -> turn_around_time - p -> burst_time;
		} else q.push(p);
	} 
	
	return;
}

/* Print average WT and average TAT */
void printAverage(vector<Process> &process) {
	int n = process.size();
	
	cout << endl;

	return;
}

int main() {
	// Number of processes
	int n;
	cin >> n;						

	// Vector of processes
	vector<Process> process(n);
	for (int i = 0; i < n; i++) {
		process[i].pid = i + 1;
		cin >> process[i].arr_time;
		cin >> process[i].burst_time;
		int a = process[i].burst_time;
		process[i].remain_time = a;
	}

	// Find Waiting Time and Turn Around Time for all processes
	solve(process);
	// Print average Wait Time and average Turn Ariund Time
	double avg_wt = 0.0;
	double avg_tat = 0.0;

	for (auto p: process) {
		avg_wt += p.wait_time;
		avg_tat += p.turn_around_time;
	}

	avg_wt /= n;
	avg_tat /= n;
	cout << fixed << setprecision(4);
	cout << avg_wt << " " << avg_tat << endl;

	// Sort vector according to finish times
	sort(process.begin(), process.end(), ft_comp);

	for (int i = 0; i < n; i++) {
		cout << "P" << process[i].pid << " ";
	}
	cout<<endl;
}