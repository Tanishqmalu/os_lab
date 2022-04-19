#include<bits/stdc++.h>
#include <sstream>
#include <string>
using namespace std;
#define ll long long int

// It stores frames which are already reserved
// memory[left_range] = right_range, i.e ([left_range,right_range] is already occupied)
unordered_map <ll, ll> memory;

// It stores page number allocated to frame number
// ans[page_number] = frame_number
map<ll,ll> ans;

// It stores the last page number used
int last;

// it stores the deleted frames in a priority queue to allot in upcoming queries
priority_queue<int> del;

// Current page_number
ll page_num=0;

ll p,v,f;
ll max_frame; // 2^(p-f)
ll free_frame; // number of frames free

ll max_page;

/* Function to allocate a new process of given size */
void allocate(ll size) {
	// Number of pages required to store given resource
    ll num_pages = ceil((double)size/(double)(pow(2,f)));
    
    // if num_pages is greater than free frames or it exceeds total page limit then error !
    if(num_pages > free_frame || num_pages + last - 1 >max_page){
        cout<<"Cannot allocate all the pages, Free frames left = "<<free_frame<<" !!\n";
        return;
    }
	cout<<size<<" bytes has been alloted to: ";
	
	while(num_pages){
		if(del.size()){
			int frame_num = del.top();
			del.pop();
			cout<<frame_num<<" ";
			ans[page_num] = frame_num;
			
			page_num++;
			num_pages--;
			continue;
		} else {
			if (memory[last] > 0 ){
				last = memory[last];
				last++;
			} // Unallowed area
				
			ans[page_num] = last;
			cout<<last<<" ";
			page_num++;
			last++;
			num_pages--;
		}
	}

	cout<<endl;
	return;
}
void delete_page(ll del_pageNo){
	if(ans.find(del_pageNo)==ans.end()){
		cout<<"Page does not exists, thus cant delete !!\n";
		return;
	}	
	ll del_frameNo = ans[del_pageNo];
	del.push(del_frameNo);
	ans.erase(del_pageNo);
	free_frame++;
	cout<<"Page number "<<del_pageNo<<" = frame number "<<del_frameNo<<" has been deleted"<<endl;
}

void translate(ll logi_addr){
	int binaryNum[32]={};
    int cnt = 0;
    while (logi_addr > 0) {
 
        // storing remainder in binary array
        binaryNum[cnt] = logi_addr % 2;
        logi_addr /= 2;
        cnt++;
    }
 	ll pid = 0;
 	
    // printing binary array in reverse order
    for (int j = cnt - 1; j >= f; j--){
    	if(binaryNum[j]){
    		pid += pow(2,j-f);
    		binaryNum[j]=0;
    	}
    }
	// page number doesnt exists
    if(ans.find(pid) == ans.end()){
    	cout<<"Invalid Page Number\n";
    	return;
    } else {
    	ll fr = ans[pid]; // finding frame alloted to given pid
    	ll ind = f;
    	while (fr > 0) { // translatinf frame number to binary and prefixing it with page offset
	        binaryNum[ind] = fr % 2;
	        fr /= 2;
	        ind++;
    	}
    	ll physical_addr = 0;
    	for (int j = ind - 1; j >= 0; j--){
	    	if(binaryNum[j]){
	    		physical_addr += pow(2,j);
	    	}
	    }
	    cout<<"The physical address is: "<<physical_addr<<endl; 
    }
}
int main(){

	cin>>p>>v>>f;
	max_frame = (1<<(p-f));
	free_frame = max_frame;
	if(v<f){
		cout<<"Invalid Input, V must be greater than f !!";
		exit(0);
	}
	max_page = (1<<(v-f));
	
	// Taking input for occupied memory
	cin.ignore();
	string s;
	getline(cin,s);
	istringstream temp(s);
	int num1;
	while(temp>>num1){
		int num2;
		temp>>num2;
		memory[num1]=num2;
		free_frame -= (num2 - num1 + 1);
	}
	
	// Taking input for queries
	char c;
    while(cin>>c){
        if(c=='a'){
			ll size;
			cin>>size;
			allocate(size);
		} else if(c=='t'){
			ll logi_addr;
			cin>>logi_addr;
			translate(logi_addr);
		} else {
			ll num;cin>>num;
			delete_page(num);			
		}
		
		cout<<endl;
    }
	
	return 0;
}