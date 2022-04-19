#include <bits/stdc++.h>

using namespace std;

/************************************************************************************/

// Structure for a page
typedef struct Page {
	int page_num;
	int position;
    int last_used;
    int time_inserted;   
} Page;

/************************************************************************************/

/* Function to print initial message */
void initialize(string algo, vector<int> page_order, int f, Page pages[]);

/* Function to print frame contents at any instant of time */
void Print_Current_Frame_state(vector<int> frame, int f, int time);

/* 	Function to change page properties.If time_inserted and position are -1
    then make no change to respective fields	*/
void updatePage(Page* page, int time_inserted, int position, int last_used);

/************************************************************************************/

/*	Function to simulate LRU page replacement */
void lru(int f, vector<int> page_order) {
    vector<int> frame;
    list<Page*> S;
    Page pages[200];
    int t = 0, page_faults = 0;
    int N = page_order.size();

    initialize("LRU", page_order, f, pages);
    Print_Current_Frame_state(frame, f, t);

    for (int i = 0; i < N; i++) {
        t++;
        Page* page = &pages[page_order[i] - 1];
        
        if ( find(S.begin(), S.end(), page) == S.end() ) {	// If page is not in the current frame
            page_faults++; 
            if ( S.size() < f ) {							// If some frames are still empty
                updatePage(page, t, frame.size(), t);
                // Insert into next frame
                frame.push_back(page -> page_num);
                S.push_back(page);
            }
            else {											// If all frames are already occupied
                updatePage(page, t, (*S.begin()) -> position, t);
                // Replace the Least Recently Used frame with current frame
                frame[page -> position] = page -> page_num;
                S.pop_front();
                S.push_back(page);
            }
        }
        else {
            S.erase(find(S.begin(), S.end(), page));
            S.push_back(page);
            updatePage(page, -1, -1, t);
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
	cout<< "LRU" << ":\n";
    for (auto ele: arr) {
        cout << ele << " ";
    }
    cout << "\nFrame content at each time step t\n";
    for (int i = 0; i < n; i++) {
        cout << "F" << i + 1 << "\t";
    }
    cout << endl;
    lru(n, arr); 
}

/************************************************************************************/
void initialize(string algo, vector<int> page_order, int f, Page pages[]) {
    for (int i = 0; i < 200; i++) {
        pages[i].page_num = i + 1;
        pages[i].position = -1;
        pages[i].last_used = -1;
        pages[i].time_inserted = -1;
    }
}

/************************************************************************************/
void Print_Current_Frame_state(vector<int> frame, int f, int time) {
    int n = frame.size();
    for (int i = 0; i < f; i++) {
        if (i < n) cout << frame[i] << "\t";
        else cout << "X\t";
    }
    cout << "at t = " << time << endl;
    return;
}

/************************************************************************************/
void updatePage(Page* page, int time_inserted, int position, int last_used) {
	if (position != -1) page -> position = position;
	page -> last_used = last_used;
    if (time_inserted != -1) page -> time_inserted = time_inserted;
}

/************************************************************************************/