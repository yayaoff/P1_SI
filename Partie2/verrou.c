#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int lockThread = 0;

void lock(){
    asm(
        "enter:"
        "movl $1, %%eax;"
        "xchgl %%eax, %0;"
        "testl %%eax, %%eax;"
        "jnz enter; "
        :"=r" (lockThread)
        :
        :"eax"
        );
    printf("%d",lockThread);
};

void unlock(){
    asm(
        "movl $0, %0 ;"
        :"=r" (lockThread)
        :
        :"eax"
        );
    printf("%d",lockThread);
    }

void sectionCritique(int N){
    for (int i = 0; i < 6400/N; i++)
    {
        while(lockThread == 1){}
    lock();
    for (int i = 0; i < 10000; i++){}
    unlock();
    }
}


int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    pthread_t Threads[N];
    for (int i = 0; i < N; i++)
    {
        if(pthread_create(&Threads[i], NULL, (void*) sectionCritique, NULL) != 0){
            printf("error");
        }
    }
    return 0;
}