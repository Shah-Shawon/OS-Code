#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // For wait()

int main(int argc, char* argv[]) {
    // Ensure at least: program name, n, and one child name
    if (argc < 3) {
        printf("Usage: %s <n> <child_1> <child_2> ...\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);  // Convert first argument to integer (number of children)

    // Check if number of names (argv) matches n
    if (argc != n + 2) {
        printf("Error: Mismatch between 'n' and number of child names provided.\n");
        exit(1);
    }

    // Create n child processes
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // Child process block
            printf("%s: PID = %d, PPID = %d\n", argv[i + 2], getpid(), getppid());
            exit(0);  // Child exits to prevent further fork
        }
        // Parent continues to next iteration
    }

    // Parent waits for all n child processes
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent process finished waiting for all child processes.\n");

    return 0;
}