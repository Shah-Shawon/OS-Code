#include <stdio.h>
#include <pthread.h>

// Shared global counter
int counter = 0;

// Function executed by both threads
void* increment() {
    for (int i = 0; i < 1000000; i++) {
        counter++;  // Not thread-safe!
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads running the same function
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter: %d\n", counter);  // Race condition likely means < 2000000
    return 0;
}