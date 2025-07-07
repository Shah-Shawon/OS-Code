#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(){
    pid_t pid = fork();

    if(pid<0){
        printf("fork failed\n");
        exit(1);
    }else if(pid==0){
        printf("zombie,child [pid = %d] is exiting.\n",getpid());
        exit(0);
    }else{
        sleep(5);
        printf("child exit,parent[pid = %d] runnig....\n",getpid());
    }
    return 0;
}