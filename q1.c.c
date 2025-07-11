/*Write a C program to create a main process named ‘parent_process’ having 3 
child processes without any grandchildren processes.  
Trace parent and child processes in the process tree.   
Show that child processes are doing addition, subtraction and multiplication 
on two variables initialized in the parent_process */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid[3];                 // Array to store child PIDs
    int a = 10, b = 5;            // Parent initializes two variables

    printf("Parent Process [PID: %d] starts.\n", getpid());

    for (int i = 0; i < 3; i++) {
        pid[i] = fork();          // Create a new child process
        if (pid[i] < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (pid[i] == 0) {
            // This is the child process
            if (i == 0)
                printf("Child 1 (Addition) [PID: %d | PPID: %d] → %d + %d = %d\n", getpid(), getppid(), a, b, a + b);
            else if (i == 1)
                printf("Child 2 (Subtraction) [PID: %d | PPID: %d] → %d - %d = %d\n", getpid(), getppid(), a, b, a - b);
            else
                printf("Child 3 (Multiplication) [PID: %d | PPID: %d] → %d * %d = %d\n", getpid(), getppid(), a, b, a * b);
            
            exit(0);  // Important: child exits after task to prevent duplicate forking
        }
    }
    sleep(20);
    // Parent waits for all child processes to complete
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent Process [PID: %d] has completed.\n", getpid());
    return 0;
}