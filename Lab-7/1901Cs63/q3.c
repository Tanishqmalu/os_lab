#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
int max_slices = 5; // maximum slices in a pizza
int slices=0;
bool has_been_ordered;
pthread_cond_t order;	//conditional variable to check if an order has been placed

pthread_cond_t deliver;	//conditional variable to check if a delivery has been made or not

pthread_mutex_t mutex;	//Associated with both Condition variables to verify proper count of slices

void *studentEatSlice(void *slice_no) {
  while(true) {
    pthread_mutex_lock(&mutex);
    if (slices > 0) {
      slices -= 1;
    }
    else {
      if(has_been_ordered == false){
        pthread_cond_signal(&order);
        has_been_ordered = true;
      }
      while (slices <= 0) {
        pthread_cond_wait(&deliver, &mutex);
      }
      slices -=1 ;
    }
    printf("Student: %d eating a slice\n", *((int *)slice_no));
    printf("Only %d / 5 remaining\n", slices);
    sleep(1);
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
}

void *DeliverPizza() {
  while(true) {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&order, &mutex);
    printf("\nDelivering a Pizza\nWake up all students\n\n");
    slices = max_slices;
    has_been_ordered = false;
    
    pthread_cond_broadcast(&deliver);
    pthread_mutex_unlock(&mutex);
  }
}

int main() {
	pthread_t student[8], delivery;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&order, NULL);
    pthread_cond_init(&deliver, NULL);

    int id[8] = {1,2,3,4,5,6,7,8}; //to use a id for a given student thread 

	// Initial delivery thread to bring a pizza
    pthread_create(&delivery, NULL, DeliverPizza, NULL);
	
	
    for(int i = 0; i < 8; i++) {
        pthread_create(&student[i], NULL, studentEatSlice, (void *)&id[i]);
    }
    
    pthread_join(delivery, NULL);

    for(int i = 0; i < 8; i++) {
        pthread_join(student[i], NULL);
    }

    pthread_cond_destroy(&deliver);
    pthread_cond_destroy(&order);
    pthread_mutex_destroy(&mutex);

    return 0;
}