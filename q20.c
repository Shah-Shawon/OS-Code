// q20.c: Compute average, min, max using threads
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int numbers[100], n;
float average;
int minimum, maximum;

// Thread function to calculate average
void* calc_average() {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += numbers[i];

    average = sum / (float)n;
    return NULL;
}

// Thread function to calculate minimum
void* calc_min() {
    minimum = numbers[0];
    for (int i = 1; i < n; i++)
        if (numbers[i] < minimum)
            minimum = numbers[i];
    return NULL;
}

// Thread function to calculate maximum
void* calc_max() {
    maximum = numbers[0];
    for (int i = 1; i < n; i++)
        if (numbers[i] > maximum)
            maximum = numbers[i];
    return NULL;
}

int main(int argc, char* argv[]) {
    // Minimum arguments check
    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments to integers
    n = argc - 1;
    for (int i = 0; i < n; i++)
        numbers[i] = atoi(argv[i + 1]);//argv[0] is the program name, and the remaining are the actual arguments.

    // Create threads
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, calc_average, NULL);
    pthread_create(&t2, NULL, calc_min, NULL);
    pthread_create(&t3, NULL, calc_max, NULL);

    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Display results
    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", minimum);
    printf("Maximum: %d\n", maximum);

    return 0;
}