#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/mman.h>

int main() {
    int* counter = mmap(NULL,sizeof(int),PROT_WRITE| PROT_READ,
                        MAP_SHARED | MAP_ANONYMOUS,-1,0);
    
    if(counter == MAP_FAILED){
        perror("mmap failed");
        exit(1);
    }
    *counter = 0;

    if(fork()==0){
        for(int i=0;i<1000000;i++){
            (*counter)++;
        }
        exit(0);
    }else{
        for(int i=0;i<1000000;i++){
            (*counter)++;
        }
        wait(NULL);
    }
    printf("Final counter: %d\n",*counter);
}