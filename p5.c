#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(int argc,char* argv[]){
    if(argc<3){
        printf("Usage:%s <n><child_1><child_2>....\n",argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);

    
}