#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct sema{
    int val;
    int sem;
}sema;

void lock(int lockThread){
    asm(
        "enter:"
        "movl $1, %%eax;"      // %eax=1
        "xchgl %%eax, %0;"     // Exchange %eax and lock : lock=1
                               // and %eax either 0(lock was free) or 1(lock wasn't free!-->loop!!)
        "testl %%eax, %%eax;"  // If %eax=0, puts the flag ZF at "true"
        "jnz enter; "          // If ZF is false, back to the start
        :"=m" (lockThread)
        :
        :"eax"
        );
};

void unlock(int lockThread){
    asm(
        "movl $0, %0 ;"         // %eax=0
        :"=m" (lockThread)      // lock=0
        :
        :"eax"                  // Return 0
        );
}

int init(sema *newSem, int valueSem){
    newSem -> val = valueSem;
    newSem -> sem = 0;
}

void wait(sema *newSem){
    while(1==1){
        lock(newSem -> sem);
        if (newSem -> val > 0){
            newSem -> val--;
            break;
        }
        unlock(newSem -> sem);
    }
    unlock(newSem -> sem);
}

int post(sema *newSem ){
    lock(newSem -> sem);
    newSem -> val++;
    unlock(newSem -> sem);
}
