int target=1; // Shared variable : either 1 or 0

// If locked, it waits until it becomes free
// If not, it takes the lock and executes the critical session

void unlock(){
    target=0;
}

int lock(){
    if(target==0) target=1;
    else{
        while(target==1) {
            //wait()
        }
    }
}

int test_and_test(int* target){
    int r = *target;
    *target = 0;
    return 0;   // Atomic operation
}

int main(){
    while(test_and_test(&lock)){}
    // Critical session
    
    target=1;
    
}
