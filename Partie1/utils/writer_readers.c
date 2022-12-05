#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_writecount;
pthread_mutex_t z;

sem_t wsem;
sem_t rsem;

int readcount = 0;
int writecount = 0;

int countw = 0;
int countr = 0;

void writer(void)
{
    int i = 1;
    while(i == 1){
        pthread_mutex_lock(&mutex_writecount);
        writecount++;
        if (writecount == 1)
        {
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&mutex_writecount);
        sem_wait(&wsem);
        if (countw < 2560){
            for (int j=0; j<10000; j++){}
            countw++;
        }
        else{
            i = 0;
        }
        sem_post(&wsem);
        pthread_mutex_lock(&mutex_writecount);
        writecount--;
        if(writecount == 0)
        { 
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&mutex_writecount);
    }
}

void reader(void)
{
    int i = 1;
    while(i == 1){
        sem_wait(&rsem);
        pthread_mutex_lock(&mutex_readcount);
        readcount++;
        if (readcount == 1)
        { 
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&mutex_readcount);
        sem_post(&rsem);
        pthread_mutex_lock(&mutex_readcount);
        if (countr < 640){
            for (int j=0; j<10000; j++){}
            countr++;
            readcount--;
            if(readcount==0)
            { 
                sem_post(&wsem);
            }
        }
        else{
            i = 0;
        }
        pthread_mutex_unlock(&mutex_readcount);
    }
}

int main(int argc, char const *argv[])
{    
    int w = atoi(argv[1]);
    int r = atoi(argv[2]);
    
    pthread_t write[w];
    pthread_t read[r];
    
    sem_init(&wsem, 0, 1);
    sem_init(&rsem, 0, 1);

    pthread_mutex_init(&mutex_readcount, NULL);
    pthread_mutex_init(&mutex_writecount, NULL);
    pthread_mutex_init(&z, NULL);
    
    for (int i = 0; i < r; i++)
    {
        if(pthread_create(&read[i], NULL, (void *)reader, NULL) != 0){
            printf("Error while creating read Thread ");
        }
    }
    for (int i = 0; i < w; i++)
    {
        if(pthread_create(&write[i], NULL, (void *)writer, NULL) != 0){
            printf("Error while creating writer Thread ");
        }
    }

    for (int i = 0; i < r; i++)
    {
        if(pthread_join(read[i], NULL) != 0){
            printf("Error while joining read threads ");
        }
    }
    for (int i = 0; i < w; i++)
    {
        if(pthread_join(write[i], NULL) != 0){
            printf("Error while joining write threads ");
        }
    }
    
    pthread_mutex_destroy(&mutex_readcount);
    pthread_mutex_destroy(&mutex_writecount);

    sem_destroy(&wsem);
    sem_destroy(&rsem);

    return 0;
}