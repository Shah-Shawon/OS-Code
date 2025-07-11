#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RESOURCES 3  // Maximum resources available at once
sem_t sem;               // Semaphore to manage resource access

// Function representing a thread trying to use a resource
void* use_resource(void* arg) {
    sem_wait(&sem);  // Request (decrement) resource
    printf("Thread %ld is using a resource\n", (long)arg);

    sleep(1);        // Simulate resource usage

    printf("Thread %ld released a resource\n", (long)arg);
    sem_post(&sem);  // Release (increment) resource
    return NULL;
}

int main() {
    pthread_t threads[5];

    // Initialize semaphore: shared between threads (2nd arg = 0), value = 3
    sem_init(&sem, 0, MAX_RESOURCES);

    // Create 5 threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, use_resource, (void*)i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&sem);
    return 0;
}

