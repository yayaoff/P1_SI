#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define N 8
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int buffer[N];

int in=0;
int j=0;
int out=8192;

void insert_item(int item){
    buffer[in]=item;
    in++;
}

int remove_item(){
    in--;
    return buffer[in];
}

void producer(void){
    int item=1;
    for (int k=0; k<10000; k++);
    bool b=true;
    while(b){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if(j<8192){
            insert_item(item);
            j++;
        }
        else {b=false;}
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void consumer(void){
    int item;
    bool b=true;
    while(b){
        sem_wait(&full); // waiting for free place
        pthread_mutex_lock(&mutex);
        if(out>0){
            item=remove_item();
            out--;
        }
        else b=false;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // one more place free
        for (int k=0; k<10000; k++);
    }
}

int main(int argc, char const *argv[]){

    int cons = atoi(argv[2]);
    int prod = atoi(argv[1]);
    pthread_t pro[prod],con[cons];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    for(int i = 0; i < prod; i++) {
        if (pthread_create(&pro[i], NULL, (void *)producer, NULL) != 0){
            printf("Error 2");
            pthread_mutex_destroy(&mutex);
            sem_destroy(&empty);
            sem_destroy(&full);
            return 1;
        }
    }
    for(int i = 0; i < cons; i++) {
        if (pthread_create(&con[i], NULL, (void *)consumer, NULL) != 0){
            printf("Error 3");
            pthread_mutex_destroy(&mutex);
            sem_destroy(&empty);
            sem_destroy(&full);
            return 1;
        };
    }
    for(int i = 0; i < prod; i++) {
        if (pthread_join(pro[i], NULL) != 0){
            printf("Error 4");
            pthread_mutex_destroy(&mutex);
            sem_destroy(&empty);
            sem_destroy(&full);
            return 1;
        };
    }
    for(int i = 0; i < cons; i++) {
        if (pthread_join(con[i], NULL) != 0){
            printf("Error 5");
            pthread_mutex_destroy(&mutex);
            sem_destroy(&empty);
            sem_destroy(&full);
            return 1;
        };
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}