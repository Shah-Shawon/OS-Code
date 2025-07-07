#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    char* names[] = {"child_1","child_2","child_3"};

    for(int i=0;i<3;i++){
        pid_t pid = fork();
        if (pid < 0) { 
            // If fork fails 
            perror("Fork failed"); 
            exit(1); 
        } else if(pid==0){
            printf("%s: PID = %d,PPID = %d\n",names[i],getpid(),getppid());
            exit(0);
        }
    }
    for(int i=0;i<3;i++){
        wait(NULL);
    }
    printf("Parent process has finished\n");
}