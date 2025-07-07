#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t pid[3];
    int b = 5, a = 10;

    printf("parent is starting, PID = %d\n",getpid());

    for(int i=0;i<3;i++){
        pid[i]=fork();

        if(pid[i]<0){
            printf("Fork fail.\n");
            exit(1);
        }
        if(pid[i]==0){
            if(i==0){
                printf("Addition, pid=%d, PPID = %d, a+b = %d\n",getpid(),getppid(),a+b);
            }else if(i==1){
                printf("Subtraction, pid=%d, PPID = %d,a-b = %d\n",getpid(),getppid(),a-b);
            } else{
                printf("Multiplication, pid=%d, PPID = %d, a*b = %d\n",getpid(),getppid(),a*b);
            }
            exit(0);
        }
    }
    for(int i=0;i<3;i++){
        wait(NULL);
    }
    printf("Parent process complete ,Pid = %d\n",getpid());
}