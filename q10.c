#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>  // Required for wait()
#include<string.h>

int main() {
    // Create a named pipe (FIFO) with read-write permissions
    mkfifo("myfifo", 0666);

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child Process: Open FIFO for reading
        int fd = open("myfifo", O_RDONLY);
        if (fd < 0) {
            perror("Child: Failed to open FIFO");
            exit(1);
        }

        char buf[100];
        read(fd, buf, sizeof(buf));
        printf("Child read: %s\n", buf);
        close(fd);
    } else {
        // Parent Process: Open FIFO for writing
        int fd = open("myfifo", O_WRONLY);
        if (fd < 0) {
            perror("Parent: Failed to open FIFO");
            exit(1);
        }

        char *msg = "Hello from writer\n";
        write(fd, msg, strlen(msg));
        close(fd);
        wait(NULL);  // Wait for child to complete
    }

    return 0;
}