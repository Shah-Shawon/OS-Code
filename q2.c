/*Write a C program to create an orphan process.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a new process 

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    } 
    else if (pid > 0) {
        // Parent process
        printf("Parent Process [PID: %d] is exiting...Child becomes orphan.\n", getpid());
        exit(0);  // Parent exits, child becomes orphan
    } 
    else {
        // Child process
        sleep(5);  // Allow time for parent to exit
        printf("Child Process [PID: %d] is now orphaned. New Parent PID (PPID): %d\n", getpid(), getppid());
    }

    return 0;
}