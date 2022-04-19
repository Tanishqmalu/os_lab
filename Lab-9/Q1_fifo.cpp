#include <bits/stdc++.h>

using namespace std;

queue<int> q;
set<int> s;

/************************************************************************************/

/* Function to print frame contents at any instant of time */
void Print_Current_Frame_state(vector<int> frame, int f, int time);

/************************************************************************************/

/*	Function to simulate FIFO page replacement */
void fifo(int f, vector<int> arr) {
   int t=0;					// setting the timer to 0
   vector<int> frame(f);	// vector to store frame
   for(int i=0;i<f;i++){
   	frame[i]=-1;
   }
   // printing current frame state
   Print_Current_Frame_state(frame,f,t);
   
   int n=arr.size();
   int curr_ind = 0;	// setting the current frame index where page needs to be stored to 0
   int page_fault = 0;	
   for(int i=0;i<n;i++){
   	t++;
   	int curr = arr[i];
   	// if page is already present
   	if(s.find(curr)!=s.end()){
   		Print_Current_Frame_state(frame,f,t);
   		continue;
   	}
   	page_fault++;
   	s.insert(curr);	// insert the page into the set and the queue
   	q.push(curr);
   	int sz = frame.size();
   	if(frame[curr_ind]==-1){   // if frames are not filled completely
   		frame[curr_ind] = curr;
   		curr_ind++;
   		curr_ind%=f;
   		Print_Current_Frame_state(frame,f,t);
   		continue;
   	}
   	int fr = q.front();
   	q.pop();
   	s.erase(s.find(fr));
   	frame[curr_ind%f] = curr;
   	curr_ind++;
   	curr_ind%=f;
   	Print_Current_Frame_state(frame,f,t);

   }
   
   cout<<endl<<"Number of page defaults: "<<page_fault<<endl;
}

/************************************************************************************/
int main() {
	int n;cin>>n;
	//int m;cin>>m;
	int a;
	vector<int> arr;
	while(cin>>a){
		arr.push_back(a);
	}

	cout<<"FIFO" << ":\n";
    for (auto ele: arr) {
        cout << ele << " ";
    }
    cout << "\nFrame content at each time step t\n";
    for (int i = 0; i < n; i++) {
        cout << "F" << i + 1 << "\t";
    }
    cout << endl;
	
    fifo(n, arr);   
}

/************************************************************************************/
void Print_Current_Frame_state(vector<int> frame, int f, int time) {
    for (int i = 0; i < f; i++) {
        if (frame[i]!=-1) cout << frame[i] << "\t";
        else cout << "X\t";
    }
    cout << "at t = " << time << endl;
    return;
}

/************************************************************************************/
