#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
  
#include<bits/stdc++.h>
using namespace std;

int cyl, head_posc, num_req;

//creating a struct for the process
struct process{
	int idx;
	int dno;
};


/* FCFS Disk Scheduling */
int fcfs(process proc[]) {
	int head_pos = head_posc;
	int HeadMove[num_req];
	int TotalHeadMovement = 0;
	ofstream fout;
	fout.open("fcfs.txt");
	fout<<0<<" "<<100<<endl;
	for (int i = 0; i < num_req; i++) {
		
		HeadMove[i] = abs(head_pos - proc[i].dno);
		//cout<<head_pos<<" "<<proc[i].dno<<" "<<HeadMove[i]<<endl;
		TotalHeadMovement += HeadMove[i];
		fout<<proc[i].idx<<" "<<proc[i].dno<<endl;
		head_pos = proc[i].dno;
	}
	fout.close();

	return TotalHeadMovement;
}

int compare (const void * a, const void * b) {
	process A = *((process*)a);
	process B = *((process*)b);
	return ( A.dno - B.dno );
}

/* Comparator for Q-Sort according to index number */
int compare_idx (const void * a, const void * b) {
	process A = *((process*)a);
	process B = *((process*)b);
	return ( A.idx - B.idx );
}
/* SCAN Disk Scheduling */
int scan(process proc[]) {
	int start = -1, idx;
	int HeadMove[num_req];
	int head_pos = head_posc;
	int TotalHeadMovement = 0;
	qsort(proc, num_req, sizeof(process), compare);
	
	ofstream fout;
	fout.open("scan.txt");
	fout<<0<<" "<<100<<endl;
	int cnt = 1;
	for (int i = num_req-1; i >-1; i--) {
		if (proc[i].dno <= head_pos) {
			if (start == -1) start = i;
			idx = proc[i].idx;
			HeadMove[idx] = head_pos - proc[i].dno ;
			TotalHeadMovement += HeadMove[idx] ;
			fout<<cnt++<<" "<<proc[i].dno<<endl;
			head_pos = proc[i].dno;
		}
	}
	TotalHeadMovement += head_pos ;
	fout<<cnt++<<" "<<0<<endl;
	head_pos = 0;
	// Reverse movement from start
	for (int i = start + 1; i<num_req; i++) {
		idx = proc[i].idx;
		HeadMove[idx] = proc[i].dno - head_pos;
		TotalHeadMovement += HeadMove[idx] ;
		fout<<cnt++<<" "<<proc[i].dno<<endl;
		head_pos = proc[i].dno;

	}
	fout.close();
	return TotalHeadMovement;
}

/* CSCAN Disk Scheduling */
int cscan(process proc[]) {
	int start = -1, idx;
	int HeadMove[num_req];
	int head_pos = head_posc;
	int TotalHeadMovement = 0;
	qsort(proc, num_req, sizeof(process), compare);
	
	ofstream fout;
	fout.open("cscan.txt");
	fout<<0<<" "<<100<<endl;
	int cnt = 1;
	for (int i = num_req-1; i >-1; i--) {
		if (proc[i].dno <= head_pos) {
			if (start == -1) start = i;
			idx = proc[i].idx;
			HeadMove[idx] = head_pos - proc[i].dno ;
			TotalHeadMovement += HeadMove[idx] ;
			fout<<cnt++<<" "<<proc[i].dno<<endl;
			head_pos = proc[i].dno;
		}
	}
	TotalHeadMovement += head_pos ;
	fout<<cnt++<<" "<<0<<endl;
	
	head_pos = cyl;
	fout<<cnt++<<" "<<cyl<<endl;
	TotalHeadMovement += cyl ;
	// Reverse movement from start
	for (int i = num_req - 1; i>start; i--) {
		idx = proc[i].idx;
		HeadMove[idx] =  head_pos - proc[i].dno;
		TotalHeadMovement += HeadMove[idx] ;
		fout<<cnt++<<" "<<proc[i].dno<<endl;
		head_pos = proc[i].dno;

	}
	fout.close();
	return TotalHeadMovement;
}
/* SSTF Disk Scheduling */
int sstf(process proc[]) {
	int done = 0;
	int HeadMove[num_req];
	int head_pos = head_posc;
	int TotalHeadMovement = 0;
	ofstream fout;
	fout.open("sstf.txt");
	fout<<0<<" "<<100<<endl;
	int cnt=1;
	while (done < num_req) {
		int min_idx = -1;
		for (int i = 0; i < num_req; i++) {
			if ( min_idx == -1 || abs(proc[i].dno - head_pos) < abs(proc[min_idx].dno - head_pos) )
				min_idx = i;
		}
		
		int idx = proc[min_idx].idx;
		HeadMove[idx] = abs(proc[min_idx].dno - head_pos);
		fout<<cnt++<<" "<<proc[min_idx].dno<<endl;
		TotalHeadMovement += HeadMove[idx];
		head_pos = proc[min_idx].dno;
		proc[min_idx].dno = INT_MAX;
		done++;
	}
	fout.close();
	return TotalHeadMovement;
}
int main(){
	cin>>cyl>>head_posc>>num_req;
	process proc[num_req];
	for(int i=0;i<num_req;i++){
		proc[i].idx = i+1;
		cin>>proc[i].dno;
	}
	int fcfs_thm = fcfs(proc);
	cout<<"Total Head Moement in FCFS = "<<fcfs_thm<<" and Seek time = "<<fcfs_thm*5<<endl;
	int scan_thm = scan(proc);
	cout<<"Total Head Movement in SCAN = "<<scan_thm<<" and Seek time = "<<scan_thm*5<<endl;
	int cscan_thm = cscan(proc);
	cout<<"Total Head Movement in C-SCAN = "<<cscan_thm<<" and Seek time = "<<cscan_thm*5<<endl;
	int sstf_thm = sstf(proc);
	cout<<"Total Head Movement in SSTF = "<<sstf_thm<<" and Seek time = "<<sstf_thm*5<<endl;
	return 0;
}