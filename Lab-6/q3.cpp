#include <bits/stdc++.h>
using namespace std;

struct processes
{
	int arrival_time;
	int burst_time;
	int newburst_time;
	int priority;
	int complete_time;
	int pid;
};

struct compareSet
{
	bool operator()(processes a, processes b)
	{
		if (a.priority != b.priority)
			return a.priority < b.priority;
		else if (a.priority == b.priority)
		{
			if(a.arrival_time != b.arrival_time)
				return a.arrival_time < b.arrival_time;
			else
				return a.pid < b.pid;
		}
	}
};

bool compare(processes a, processes b)
{
	if (a.arrival_time < b.arrival_time)
		return true;
	else if (a.arrival_time == b.arrival_time)
		return a.pid < b.pid;
	else
		return false;
}

vector<processes> solve(int n, int tq, vector<processes> v, set<processes, compareSet> s)
{
	int time = 0;
	int numberOfProcesses = n;
	int it = 0;
	vector<processes> completion;
	long int totalWaitingTime = 0;
	int totalTurnAroundTime = 0;
	while (numberOfProcesses)
	{
		if (s.empty())
		{
			s.insert(v[it]);
			time = v[it].arrival_time;
			it++;
		}
		processes currentProcess = *s.begin();
		s.erase(currentProcess);

		time += currentProcess.newburst_time;
		currentProcess.newburst_time = 0;

		currentProcess.complete_time = time;
		completion.push_back(currentProcess);
		numberOfProcesses--;
		totalTurnAroundTime = totalTurnAroundTime + (time - currentProcess.arrival_time);
		totalWaitingTime = totalWaitingTime + (time - currentProcess.arrival_time - currentProcess.burst_time);
		while (it < n && v[it].arrival_time <= time)
		{
			s.insert(v[it]);
			it++;
		}
	}

	printf("%0.2f %0.2f\n", (float)totalWaitingTime / (float)n, (float)totalTurnAroundTime / (float)n);

	return completion;
}

int main()
{
	int n, tq;
	cin >> n;
	vector<processes> v;
	set<processes, compareSet> s;

	for (int i = 0; i < n; i++)
	{
		processes process;
		cin >> process.arrival_time >> process.burst_time >> process.priority;
		process.newburst_time = process.burst_time;
		process.pid = i + 1;
		v.push_back(process);
	}

	sort(v.begin(), v.end(), compare);
	
	vector<processes> completion = solve(n, tq, v, s);

	for (int i = 0; i < n; i++)
		cout << "P" << completion[i].pid << " ";
	cout << endl;

	return 0;
}