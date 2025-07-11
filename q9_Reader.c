// fifo_reader.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char buf[100];

    // Open the FIFO for reading
    int fd = open("myfifo", O_RDONLY);
    if (fd < 0) {
        perror("Open failed");
        return 1;
    }

    // Read message from the pipe
    read(fd, buf, sizeof(buf));

    // Print the received message
    printf("Reader got: %s", buf);

    // Close the FIFO
    close(fd);

    return 0;
}