#include <pthread.h>   
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NUMTHREAD 3      /* number of threads */
#define LIMIT 1000         /* treasure Balance */
void * depositor(void*);
void * withdrawer(void*);
void * hacker(void*);
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t belowLimit  = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD]  = {0,1,2};
// int i = 0, j = 0;
/* shared variable */
int balance = LIMIT;
int required=0;
int main()
{
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];
    /* create 2 threads*/
    /* create one depositor and one withdrawer */
    pthread_create(&thread[0], NULL, (void *)depositor, (void*)&thread_id[0]);
    pthread_create(&thread[2], NULL, (void *)withdrawer, (void*)&thread_id[2]);
    pthread_create(&thread[1], NULL, (void *)hacker, (void*)&thread_id[1]);
    for(i=0; i< NUMTHREAD ; i++)
        pthread_join(thread[i], NULL);
    return 0;
}
void * depositor(void *arg)
{
    int *id;
    int deposit;
    id = (int*)arg;
    while(1)
    {
        // deposit = (int)(rand() % 100);/* generate a random amt of deposit?*/
        if(balance==0)
            pthread_exit(arg);
        else
        {
            /* lock the variable */
            pthread_mutex_lock(&count_mutex);
            // balance += deposit;
            // printf("          deposited :%d balance is %d: by %d\n", deposit, balance, *id);
            if(balance<LIMIT) printf("Deposited.....\n");
            balance= LIMIT;
            fflush(stdout);
            if (balance >= LIMIT)
            {
                // pthread_cond_signal(&belowLimit);
                pthread_cond_broadcast(&belowLimit);
            }
            /* Unlock the variable */
            pthread_mutex_unlock(&count_mutex);
            sleep(1);
        }
    }
}
void * withdrawer(void *arg)
{
    int *id;
    int debt;
    id = (int*)arg;
    while(1)
    {   
        printf("Enter the ammount ot withdraw: ");
        scanf("%d",&debt);
        if(balance==0)
            pthread_exit(arg);
        else
        {
            /* lock the variable */
            pthread_mutex_lock(&count_mutex);
            if (balance < debt)
            {
                printf("Call depositer to deposit.\n");
                pthread_cond_wait(&belowLimit, &count_mutex);
            }
            else
            {
                balance -= debt;
                printf("withdraw %d : by  :%d: balance %d\n",debt, *id, balance);
            }
            /*unlock the variable*/
            pthread_mutex_unlock(&count_mutex);
            fflush(stdout);
            sleep(1);
        }
    } 
}
void * hacker(void *arg)
{
    int *id;
    int debt;
    id = (int*)arg;
    //sleep haker for some time
    sleep(30);
    /*lock the variable*/
    pthread_mutex_lock(&count_mutex);
            balance = 0;
            printf("withdraw %d : by  : HAcKeR : balance %d\n", debt, balance);
    /*unlock the variable*/
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(arg);
}