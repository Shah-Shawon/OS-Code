// fifo_writer.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include<string.h>

int main() {
    // Create named pipe (FIFO) with read/write permissions
    mkfifo("myfifo", 0666);

    // Open the FIFO for writing
    int fd = open("myfifo", O_WRONLY);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    // Write a message into the pipe
    char *msg = "Hello from writer\n";
    write(fd, msg, strlen(msg));

    // Close the FIFO
    close(fd);

    return 0;
}
