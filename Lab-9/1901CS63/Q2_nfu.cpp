#include<bits/stdc++.h>
using namespace std;

// Basic principle of this algo:
/*
* Maintain a count of each page's usage
* On encountering a new page remove the page with least count
* If count of minimum usage of page is same for two pages remove page which came earlier
*
*/


// Functino to print current frame state
void Print_Current_Frame_state(vector<int> frame,int f, int time) {
    int n = frame.size();
    for (int i = 0; i < f; i++) {
        if (frame[i]!=-1) cout << frame[i] << "\t";
        else cout << "X\t";
    }
    cout << "at t = " << time << endl;
    return;
}

// comparator to sort pairs 
bool cmp(pair<int, pair<int,int>>& a,pair<int, pair<int,int>>& b){
	
    return a.second.first < b.second.first;
}

int main(){
	int n;cin>>n;

	int pagefault=0;
	int a;
	vector<int> arr;
	while(cin>>a){
		arr.push_back(a);
	}
	int m=arr.size();
	cout<< "NFU" << ":\n";
    for (auto ele: arr) {
        cout << ele << " ";
    }
    cout << "\nFrame content at each time step t\n";
    for (int i = 0; i < n; i++) {
        cout << "F" << i + 1 << "\t";
    }
    cout << endl;
	
	// mp[pagenum] = {count,frame};
	unordered_map<int,pair<int,int> > mp;	// a map to keep track of count and frame of page

	vector<int> frame(n); // vector to store frame state
	for(int i=0;i<n;i++){
		frame[i]=-1;	// initializing to -1
	}
	set<int> s;			// set to check if any page is already present or not

    int curr_ind=0;	// setting the current frame index where page needs to be stored to 0
	int t=0; 	// setting the timer to 0
	int cnt=0;	// setting the cnt to 0
	bool frame_is_full=false;	// bool to check if all the frames have been filled 

	for(int i=0;i<m;i++){
		t++;
		// if page is already present
		if(s.find(arr[i])!=s.end()){ 
			mp[arr[i]].first++;					// mp[pagenum] = {count,frame};
			Print_Current_Frame_state(frame,n,t);
			continue;
		}	
		// if page not present
		if(frame_is_full){		// if frames are not empty
			 vector<pair<int, pair<int,int>> > A;

			for (auto it : mp) {
				pair<int, pair<int,int>> x;
				x.first = it.first;
				x.second.first = it.second.first;
				x.second.second = it.second.second;
			    A.push_back(x);
			}
				
			// Sort using comparator function
			sort(A.begin(), A.end(), cmp);	// sorting to find the page with least count

			int pagenum = A.begin()->first;
			int framenum = A.begin()->second.second;
			
			mp.erase(pagenum);	// remove the page from map and set
			s.erase(pagenum);
			s.insert(arr[i]);	// insert new page
			frame[framenum] = arr[i];
			mp[arr[i]].first = 1;
			mp[arr[i]].second = framenum;
			pagefault++;		// increase the count of pagedefault
			Print_Current_Frame_state(frame,n,t);
		} else {				// if frames are empty
			pagefault++;
			s.insert(arr[i]);
			mp[arr[i]].first = 1;
			mp[arr[i]].second = curr_ind;
			frame[curr_ind] = arr[i];
			curr_ind++;
			if(curr_ind == n)frame_is_full = true;
			Print_Current_Frame_state(frame,n,t);
		}
	
			
	}
	cout<<endl<<"Number of page defaults: "<<pagefault<<endl;
	return 0;
}