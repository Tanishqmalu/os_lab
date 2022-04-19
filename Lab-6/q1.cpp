#include<bits/stdc++.h>
using namespace std;
void solve_wait_time(int arrival_time[], int n, float bt[], float wt[])
{
	wt[0] = 0;
	float cur_tim = bt[0];
	for (int i = 1; i < n ; i++ ){
		float wait_time = cur_tim - arrival_time[i];
		if(wait_time < 0) wait_time=0;
		wt[i] = wait_time;
		cur_tim += bt[i];
		}
}

// Function to calculate turn around time
void solve_TurnAround_Time( int arrival_time[], int n,	float bt[], float wt[], float tat[])
{
	// calculating turnaround time by adding
	// bt[i] + wt[i]
	
	for (int i = 0; i < n ; i++){ 
		tat[i] = wt[i] + bt[i];
		}
}

//Function to calculate average waiting time and turnaround time
void solve( int arrival_time[], int n, float burst_time[])
{
	float wait[n], turn_around_time[n], total_wait = 0, total_tat = 0;

	//Function to find waiting time of all processes
	solve_wait_time(arrival_time, n, burst_time, wait);

	//Function to find turn around time for all processes
	solve_TurnAround_Time(arrival_time, n, burst_time, wait, turn_around_time);

	//result
	printf("arrivaltime Burst time Waiting time Turn around time\n");
	
	cout << fixed << setprecision(2);
	for (int i=0; i<n; i++)
	{
		total_wait = total_wait + wait[i];
		total_tat = total_tat + turn_around_time[i];
		cout<<" "<<arrival_time[i]<<"	 "<<burst_time[i] <<"	 "<<wait[i]<<"	 "<<turn_around_time[i]<<endl;
	}
	
	float ans1=(float)total_wait / (float)n;
	float ans2=(float)total_tat / (float)n;
	cout<< " Average waiting time = "<<ans1<<endl;
	cout<< " Average turn around time = "<<ans2<<endl;
	
}

int main()
{
	int n;
	scanf("%d",&n);
	int arrival_time[n];
	float burst_time[n];
	for(int i=0;i<n;i++){
		scanf("%d",&arrival_time[i]);
		scanf("%f",&burst_time[i]);
	}

	solve(arrival_time, n, burst_time);
	return 0;
}
