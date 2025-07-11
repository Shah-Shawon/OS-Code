#include <stdio.h>
#include <fcntl.h>         // For O_CREAT, O_RDWR
#include <sys/mman.h>      // For shm_open, mmap
#include <unistd.h>        // For ftruncate, close

int main() {
    // Create shared memory object
    int fd = shm_open("shared", O_CREAT | O_RDWR, 0666);

    // Set size of shared memory to 1024 bytes
    ftruncate(fd, 1024);

    // Map shared memory into process address space (write-only)
    int* counter = mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);

    // Initialize and increment counter
    *counter = 0;
    for (int i = 0; i < 100000; i++) {
        ++(*counter);
    }

    // Cleanup: close file descriptor
    close(fd);
    return 0;
}

