#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>  // Needed for wait()

int main() {
    // Create shared memory for counter
    int* counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Create shared memory for unnamed semaphore
    sem_t* sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Initialize shared counter and semaphore
    *counter = 0;
    sem_init(sem, 1, 1);  // '1' => shared between processes

    // Fork to create child process
    if (fork() == 0) {
        // Child process increments counter with semaphore protection
        for (int i = 0; i < 100000; i++) {
            sem_wait(sem);     // Lock
            (*counter)++;      // Critical section
            sem_post(sem);     // Unlock
        }
        exit(0);
    } else {
        // Parent process increments counter with semaphore protection
        for (int i = 0; i < 100000; i++) {
            sem_wait(sem);
            (*counter)++;
            sem_post(sem);
        }

        // Wait for child to finish
        wait(NULL);

        // Print final result
        printf("Final counter: %d\n", *counter);  // Expected: 200000

        // Destroy semaphore after use
        sem_destroy(sem);
    }

    return 0;
}