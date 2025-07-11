#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // For wait()

int global = 10;  // Global variable (shared before fork)

int main() {
    int local = 5;  // Local variable (stack memory)
    
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        global += 10;
        local += 10;
        printf("Child Process: global = %d, local = %d\n", global, local);
    } 
    else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Parent Process: global = %d, local = %d\n", global, local);
    }

    return 0;
}