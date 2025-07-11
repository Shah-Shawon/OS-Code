#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>  // For wait()

int main() {
    int fd[2];              // fd[0]: read end, fd[1]: write end
    char buffer[50];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(fd[1]);  // Close unused write end
        read(fd[0], buffer, sizeof(buffer));  // Read message from parent
        printf("Child received: %s\n", buffer);
        close(fd[0]);  // Close read end
    } else {
        // Parent process
        close(fd[0]);  // Close unused read end
        char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg) + 1);  // Write message to pipe
        close(fd[1]);  // Close write end
        wait(NULL);    // Wait for child to finish
    }

    return 0;
}