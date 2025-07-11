/*Write a C program to create a zombie process.*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        // Error in creating process
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) {
        // Parent process: does NOT call wait(), so child becomes zombie
        sleep(60);  // Keep parent alive to observe the zombie child
        printf("Parent running (PID: %d). Check zombie using ps.\n", getpid());
    }
    else {
        // Child process: exits immediately
        printf("Child process (PID: %d) exiting...\nChild becomes Zombie.\n", getpid());
        exit(0);
    }

    return 0;
}