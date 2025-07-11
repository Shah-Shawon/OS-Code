#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Thread function
void* thread_function(void* arg) {
    printf("Thread here\n");
    return NULL;
}

int main() {
    pthread_t t;

    // Create a thread
    pthread_create(&t, NULL, thread_function, NULL);

    // Sleep to ensure thread executes before fork()
    sleep(1);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child (after fork), only one thread here.\n");

        // Replace child process with "ls" command
        execlp("ls", "ls", NULL);

        // Only executes if execlp() fails
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process waits for child
        wait(NULL);
        printf("Parent process done.\n");
    }

    // Ensure main waits for the thread to finish
    pthread_join(t, NULL);
    return 0;
}

