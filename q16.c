#include <stdio.h>
#include <pthread.h>

// Shared global counter
int counter = 0;

// Mutex to protect access to counter
pthread_mutex_t lock;

// Function executed by both threads
void* increment() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);   // Acquire lock
        counter++;                   // Safely increment shared counter
        pthread_mutex_unlock(&lock); // Release lock
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create two threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print the final counter value
    printf("Final counter: %d\n", counter);  // Expected: 2000000

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}