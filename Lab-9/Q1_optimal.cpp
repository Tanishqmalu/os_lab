#include <bits/stdc++.h>

using namespace std;

/************************************************************************************/

/* Function to print frame contents at any instant of time */
void Print_Current_Frame_state(vector<int> frame, int f, int t); 

/************************************************************************************/

/*	Function to simulate Optimal page replacement */
void optimal(int f, vector<int> arr) {
    vector<int> frame;
    int t = 0;
    int page_faults = 0;
    int n = arr.size();
	set<int> s;
    Print_Current_Frame_state(frame, f, t);

    for (int i = 0; i < n; i++) {
        t++;
        if (s.find(arr[i]) == s.end()) {	// If page is not in the current frame
            page_faults++;
            s.insert(arr[i]);
            if (frame.size() < f) 			// If some frames are still empty
            	frame.push_back(arr[i]);
            else {							// If no frames empty
        
                int ind = 0;
                int ans = 0;
                for (int j = 0; j < frame.size(); j++) {
                    int check = INT_MAX;
                    for (int k = i + 1; k < n; k++) {
                        if (arr[k] == frame[j]) {
                            check = k - i;
                            break;
                        }
                    }
                    if (check > ans) {
                        ans = check;
                        ind = j;
                    }
                }
                
                s.erase(s.find(frame[ind]));
                frame[ind] = arr[i];		// Replace the page which is not required
                s.insert(frame[ind]);
            }
        }
        Print_Current_Frame_state(frame, f, t);
    }
    cout <<endl<<"Number of page defaults: "<< page_faults << endl;
    return;
}
/************************************************************************************/

int main() {
	int n;cin>>n;
	int a;
	vector<int> arr;
	while(cin>>a){
		arr.push_back(a);
	}
	cout<< "Optimal" << ":\n";
    for (auto ele: arr) {
        cout << ele << " ";
    }
    cout << "\nFrame content at each time step t\n";
    for (int i = 0; i < n; i++) {
        cout << "F" << i + 1 << "\t";
    }
    cout << endl;
    optimal(n,arr);
}

/************************************************************************************/
// Function to print current frame state
void Print_Current_Frame_state(vector<int> frame, int f, int t) {
    int N = frame.size();
    for (int i = 0; i < f; i++) {
        if (i < N) cout << frame[i] << "\t";
        else cout << "X\t";
    }
    cout << "at t = " << t << endl;
    return;
}

/************************************************************************************/