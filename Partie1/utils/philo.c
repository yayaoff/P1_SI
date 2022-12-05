// Probleme des N hihi

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int N;
pthread_t *phil;
pthread_mutex_t *baguette;

void mange(int id) {};

void penser(int id){};

void philosophe (void* arg)
{
  int * idl = (int*) arg;
  int left = *idl;
  int M = (N==1) ? N+1 : N;
  int right = (left + 1) % M;
  for (int j = 0; j < 100000; j++) {
    // philosophe pense
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    mange(*idl);
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
    penser(*idl);
  }
}

int main ( int argc, char *argv[])
{
    N = atoi(argv[1]);
    long i;
    int id[N];
    int M = (N==1) ? N+1 : N;
    baguette = (pthread_mutex_t *) malloc(M * sizeof(pthread_mutex_t));
    if (!baguette){
      printf("Error");
      return 1;
    };
    phil = (pthread_t *) malloc(N*sizeof(pthread_t));
    if (!phil){
      printf("Error");
      return 1;
    };

    for (i = 0; i < N; i++){
      id[i]=i;
    }

    for (i = 0; i < M; i++){
      if (pthread_mutex_init( &baguette[i], NULL) != 0){
        printf("Error");
        free(baguette);
        free(phil);
        return 1;
      };
    }

    for (i = 0; i < N; i++){
      if(pthread_create(&phil[i], NULL, (void*) philosophe, (void*)&(id[i]) ) != 0){
        printf("Error");
        free(baguette);
        free(phil);
        return 1;
      };
    }

    for (i = 0; i < N; i++){
      if(pthread_join(phil[i], NULL)!= 0){
        printf("Error");
        free(baguette);
        free(phil);
        return 1;
      };
    }

    for (int i = 0; i < M; i++)
    {
      if(pthread_mutex_destroy(&baguette[i]) != 0){
        printf("Error");
        free(baguette);
        free(phil);
        return 1;
      };
    }

    free(baguette);
    free(phil);
    return 0;
}