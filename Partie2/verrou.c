#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int lockThread = 0;
int N;

void lock(){
    asm(
        "enter:"
        "movl $1, %%eax;"      // %eax=1
        "xchgl %%eax, %0;"     // Exchange %eax and lock : lock=1
                               // and %eax either 0(lock was free) or 1(lock wasn't free!-->loop!!)
        "testl %%eax, %%eax;"  // If %eax=0, puts the flag ZF at "true"
        "jnz enter; "          // If ZF is false, back to the start
        :"=r" (lockThread)
        :
        :"eax"
        );
};

void unlock(){
    asm(
        "movl $0, %0 ;"         // %eax=0
        :"=r" (lockThread)      // lock=0
        :
        :"eax"                  // Return 0
        );
    }

void test_and_set(void){
    lock();
    for (int i = 0; i < 10000; i++){}
    unlock();
}


int main(int argc, char const *argv[])
{
    N = atoi(argv[1]);
    pthread_t Threads[N];
    for (int i = 0; i < N; i++)
    {
        if(pthread_create(&Threads[i], NULL, (void*)&test_and_set, NULL) != 0){
            printf("error");
            return 1;
        }
    }
    for (int i = 0; i < N; i++)
    {
        if(pthread_join(Threads[i], NULL) != 0){
            printf("error");
            return 1;
        }
    }
    
    return 0;
}