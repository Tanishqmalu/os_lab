#include <bits/stdc++.h>
using namespace std;

// A class of a single processes
class Process {
public:
	int pid;				// Process ID
	int arr_time;			// Arrival Time
	int burst_time;			// Burst Time
	int wait_time;			// Waiting Time
	int fin_time;			// Finish Time
	int turn_around_time;	// Turn Around Time
	int remain_time;		// Remaining Time
	bool isFinish;
	bool inQueue;
};

bool compareFinish(Process p1, Process p2);
bool compareArrival(Process p1, Process p2);
void roundRobin(vector<Process> &processes, int quantum);
void printingAvg(vector<Process> &processes);
void enterNew(vector<Process> &processes, int time, queue<int> &mQueue);
void enterInQueue(vector<Process> &processes, int quantum, queue<int> &mQueue, int &time, int &processComplete );

int main(){
	
	cout<<"Write the no of processes(n): ";
	int n;  //no of processes
	cin >> n;						
	cout<<"Enter the time quantum: ";
	int quantum;
	cin>>quantum;
	
	vector<Process> processes(n); //vector to store the data of processes
	
	for (int i = 0; i < n; i++){
		processes[i].pid = i + 1;
		cin >> processes[i].arr_time >> processes[i].burst_time;
		processes[i].remain_time = processes[i].burst_time;
	}

	// To find the waiting time and turn around time for all the proceeses
	roundRobin(processes,quantum);
	
	// To print the waiting time and turn around time for all the proceeses
	printingAvg(processes);
}

// To sort according to the finish times 
bool compareFinish(Process p1, Process p2){
	return p1.fin_time < p2.fin_time;
}

// To sort according to the arrival times 
bool compareArrival(Process p1, Process p2){
	if (p1.arr_time == p2.arr_time){
		return p1.pid < p2.pid;
	} 
	else{
		return p1.arr_time < p2.arr_time;
	}
}

//This function take sinto consideration every new addition
// Amd push iyt in the queue accordingly
void enterNew(vector<Process> &processes, int time, queue<int> &mQueue){
	int n = processes.size();
	for(int i=0;i<n;i++){
		if(processes[i].arr_time <= time && !processes[i].inQueue && !processes[i].isFinish){
			processes[i].inQueue = true;
			mQueue.push(i);
		}
	}
}

//This checks the process at every teration
void enterInQueue(vector<Process> &processes, int quantum, queue<int> &mQueue, int &time, int &processComplete ){
	int i = mQueue.front();
	mQueue.pop();
	int n = processes.size();
	
	//If we know that teh process will be complete now
	//So we will upadet pur queue and remove this process
	//And upadet its finish time and wt and turn_around_time
	if(processes[i].remain_time <= quantum){
		processes[i].isFinish = true;
		time += processes[i].remain_time;
		processes[i].fin_time = time;
		processes[i].wait_time = processes[i].fin_time - processes[i].arr_time - processes[i].burst_time;
		processes[i].turn_around_time = processes[i].wait_time + processes[i].burst_time;
		
		if(processes[i].wait_time<0){
			processes[i].wait_time = 0;
		}
		processes[i].remain_time = 0;
		
		if(processComplete != n){
			enterNew(processes, time, mQueue);
		}
	}
	
	//if teh process is not completed
	// we will minus the time quanm 
	// amd push it in the back of queue
	else{
		processes[i].remain_time -= quantum;
		time += quantum;
		if(processComplete != n){
			enterNew(processes, time, mQueue);
		}
		mQueue.push(i);
	}
}

// First Come First Serve Algorithm
void roundRobin(vector<Process> &processes, int quantum){
	int n = processes.size();
	int time = 0;
	int processComplete = 0; //counter of how many progarm are completed;
	
	//We first sort the vector according to their arrival times
	sort(processes.begin(), processes.end(), compareArrival);
	
	queue <int> mainQueue;
	mainQueue.push(0);
	processes[0].inQueue = true;
	
	//for every new process we will update the queue
	//SO that we can keep a check on when any process is entering the cpu
	while(!mainQueue.empty()){
		enterInQueue(processes, quantum, mainQueue, time, processComplete);
	}
	
	return;
}

/* Print average wait_time and average turn_around_time */
void printingAvg(vector<Process> &processes){
	double waitingTimeAvg = 0.0;
	double turnAroundAvg = 0.0;
	int n = processes.size();

	//we add all the avg wait_time and turn_around_time
	//so that we can find teh avg by diving by n
	for(auto p: processes){
		waitingTimeAvg = waitingTimeAvg + p.wait_time;
		turnAroundAvg = turnAroundAvg + p.turn_around_time;
	}

	//because we want 2decimal places
    cout << fixed << setprecision(2);
	waitingTimeAvg /= n;
	turnAroundAvg /= n;
	cout << waitingTimeAvg << " " << turnAroundAvg << endl;

	//We first sort the vector according to their finish times
	sort(processes.begin(), processes.end(), compareFinish);

	for (int i = 0; i < n; i++){
		cout << "P" << processes[i].pid << " ";
	}
	cout << endl;

	return;
}