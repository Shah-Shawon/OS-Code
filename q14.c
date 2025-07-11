#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>//used to create shared memory
#include <sys/wait.h>  // For wait()

int main() {
    // Create anonymous shared memory for an integer
    int* counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (counter == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    *counter = 0;  // Initialize shared counter

    // Create child process using fork()
    if (fork() == 0) {
        // Child process: increment counter 100,000 times
        for (int i = 0; i < 100000; i++) {
            (*counter)++;
        }
        exit(0);  // Child exits after done
    } else {
        // Parent process: also increments counter 100,000 times
        for (int i = 0; i < 100000; i++) {
            (*counter)++;
        }

        wait(NULL);  // Wait for child process to finish

        // Print final counter value
        printf("Final counter: %d\n", *counter);
    }

    return 0;
}