#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int numbers[100],n;
float average;
int maximum,minimum;

void* calc_average(){
    int sum = 0;
    for(int i=0;i<n;i++){
        sum+=numbers[i];
    }
    average = sum/(float)n;
    return NULL;
}

void* clac_maxi(){
    maximum = numbers[0];
    
    for(int i=1;i<n;i++){
        if(maximum<numbers[i]){
            maximum = numbers[i];
        }
    }
    return NULL;
}

void* calc_min(){
    minimum = numbers[0];
    for(int i=1;i<n;i++){
        if(minimum>numbers[i]){
            minimum = numbers[i];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]){

    if(argc < 2) {
        printf("Usage: %s <list of intergers>\n",argv[0]);
        return 1;
    }

    n = argc - 1;

    for(int i=0;i<n;i++){
        numbers[i] = atoi(argv[i+1]);
    }


    pthread_t t_average,t_maximum,t_minimum;

    pthread_create(&t_average,NULL,calc_average,NULL);
    pthread_create(&t_minimum,NULL,calc_min,NULL);
    pthread_create(&t_maximum,NULL,clac_maxi,NULL);

    pthread_join(t_average,NULL);
    pthread_join(t_minimum,NULL);
    pthread_join(t_maximum,NULL);

    printf("The average value is %f\n",average);
    printf("The minimum value is %d\n",minimum);
    printf("The maximum value is %d\n",maximum);

     return 0;
}