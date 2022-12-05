#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define N 8
#define MaxItems 8192
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int* buffer;
int ind=0;
int j=0;

void insert_item(int item){
    buffer[ind]=item;
}

void producer(void){
    int item;
    int i=0;
    while(i<MaxItems){
        for (int k=0; k<1000; k++);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        insert_item(item);
        ind=(ind+1)%N;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        i++;
    }
}

void consumer(void){
    int i=0;
    int item;
    while(i<MaxItems)
    {
        sem_wait(&full); // waiting for free place
        pthread_mutex_lock(&mutex);
        item=buffer[j];
        j=(j+1)%N;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // one more place free
        for (int k=0; k<1000; k++);
        i++;
    }
}

int main(int argc, char const *argv[]){

    buffer=malloc(N*sizeof(int));
    int cons = atoi(argv[2]);
    int prod = atoi(argv[1]);
    pthread_t pro[cons],con[prod];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    for(int i = 0; i < prod; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, NULL);
    }
    for(int i = 0; i < cons; i++) {
         pthread_create(&con[i], NULL, (void *)consumer, NULL);
    }
    for(int i = 0; i < prod; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < cons; i++) {
        pthread_join(con[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}