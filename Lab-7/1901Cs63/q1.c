#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include<time.h>
// To compile:
//g++ -o q1 q1.c -lm -pthread -fopenmp

sem_t wrt;
pthread_mutex_t mutex;
int readcnt = 0;

void *writer(void *writer_no)
{   
    sem_wait(&wrt);
    printf("Writer %d writing in file\n",(*((int *)writer_no)));
    sem_post(&wrt);

}
void *reader(void *reader_no)
{  	 

    // Reader acquire the lock before modifying readcnt
    pthread_mutex_lock(&mutex);
    readcnt++;
    if(readcnt == 1) {
        sem_wait(&wrt); // if first reader, then it will block other writers
    } 
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: read cnt as %d\n",*((int *)reader_no),readcnt);
    // Reading Section
    // this segment of code helps us see how other threads are working by increasing the runtime of any given thread
	int nop=0;
	while(nop<1000000){
		nop++;
	}
    // Reader acquire the lock before modifying readcnt
    pthread_mutex_lock(&mutex);
    readcnt--;
    if(readcnt == 0) {
        sem_post(&wrt); // last reader, writer can now write
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[5],write[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int id1[5] = {1,2,3,4,5}; // to use a id for a given reader thread 
    int id2[2] = {1,2}; // // to use a id for a given writer thread
	int w_cnt=0, r_cnt=0;
	srand(time(0)); // generating random seed
	while(1) {
		if(r_cnt == 5 && w_cnt==2)break;
		int x = rand()%2; // to generate a random thread to get better results
		if(w_cnt==2)x=0;
		if(r_cnt==5)x=1;
		if(x==0){
			r_cnt++;
			pthread_create(&read[r_cnt-1], NULL, reader, (void *)&id1[r_cnt-1]);
			
		} else{
			w_cnt++;
			pthread_create(&write[w_cnt-1], NULL, writer, (void *)&id2[w_cnt-1]);
		}
    
        
        
	}

    
    for(int i = 0; i < 5; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}