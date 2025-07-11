/*Write a C program to create a main process named ‘parent_process’ having 
‘n’ child processes without any grandchildren processes. Child Processes’ 
names are child_1, child_2, child_3,......., child_n. Trace the position in the 
process tree. Number of child processes (n) and name of child processes will 
be given in the CLI of Linux based systems.  
 
Example: 
$ ./parent_process 3 child_1 child_2 child_3  */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // For wait()

int main() {
    // Array of names for the child processes
    char* names[] = {"child_1", "child_2", "child_3"};

    // Loop to create 3 child processes
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();  // Create a new process

        if (pid < 0) {
            // If fork fails
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // Child process block
            printf("%s: PID = %d, PPID = %d\n", names[i], getpid(), getppid());
            exit(0);  // Important: child exits to prevent further forking
        }
        // Parent continues looping to create next child
    }
    sleep(60);
    // Parent waits for all 3 children to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process has finished waiting for all child processes.\n");

    return 0;
}