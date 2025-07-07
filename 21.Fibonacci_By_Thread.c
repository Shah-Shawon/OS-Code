#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int *fib;
int n;

void* calc_fibo() {
    fib[0] = 0;
    if(n>1){
        fib[1] = 1;
    }
    for(int i=2;i<n;i++){
        fib[i] = fib[i-1]+fib[i-2];
    }
    return NULL;
}

int main(int argc,char* argv[]){
    if(argc!=2){
        printf("Usage: %s <n>\n",argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    fib = malloc(sizeof(int)*n);
    if(fib == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    pthread_t thread;
    pthread_create(&thread,NULL,calc_fibo,NULL);
    pthread_join(thread,NULL);

    printf("Fibonacci series: \n");
    for(int i=0;i<n;i++){
        printf("%d ",fib[i]);
    }printf("\n");

    free(fib);
    return 0;
}