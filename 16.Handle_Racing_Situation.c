#include<stdio.h>
#include<pthread.h>

int counter = 0;

pthread_mutex_t lock;

void* incremet(){
    for(int i=0;i<1000000;i++){
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t t1,t2;
    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1,NULL,incremet,NULL);
    pthread_create(&t2,NULL,incremet,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("final counter: %d\n",counter);

    pthread_mutex_destroy(&lock);

    return 0;
}