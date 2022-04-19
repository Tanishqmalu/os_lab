#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, data;

void* A()
{
    sem_wait(&mutex);
    sem_wait(&data);
    printf("process A\n");
    sem_post(&mutex);
    sem_post(&data);
}

void* B() 
{
    sem_wait(&mutex);
    sem_wait(&data);
    printf("process B\n");
    sem_post(&data);
    sem_post(&mutex);
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&data,0,1);
    pthread_t thread1, thread2;
    srand(time(0));
    int x = rand()%2;
    // To randomize thread creation to see better results
    if(x==0){
    	    pthread_create(&thread1, NULL, A, NULL);
    		pthread_create(&thread2, NULL, B, NULL);
    		pthread_join(thread1,NULL);
    		pthread_join(thread2,NULL);
    } else {
    		pthread_create(&thread1, NULL, B, NULL);
    		pthread_create(&thread2, NULL, A, NULL);
    		pthread_join(thread1,NULL);
    		pthread_join(thread2,NULL);
    }


}