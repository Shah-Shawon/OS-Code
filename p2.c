#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(){
    pid_t pid = fork();

    if(pid<0){
        printf("Fork failed...\n");
    }else if(pid==0){
        //child
        sleep(5);
        printf("Child Process pid = %d, is now orphaned. New parent Pid = %d\n",getpid(),getppid());
    }else{
        printf("Parent is exiting pid = %d.\n",getpid());
        exit(0);
    }
}