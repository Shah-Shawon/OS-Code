#include <stdio.h>
#include <fcntl.h>         // For O_RDONLY
#include <sys/mman.h>      // For shm_open, mmap
#include <unistd.h>        // For sleep, close

int main() {
    // Open the existing shared memory in read-only mode
    int fd = shm_open("shared", O_RDONLY, 0666);

    // Map shared memory into process address space (read-only)
    int* counter = mmap(0, 1024, PROT_READ, MAP_SHARED, fd, 0);

    // Wait for writer to finish (quick and dirty sync)
    sleep(2);

    // Read and print the counter value
    printf("Counter: %d\n", *counter);

    // Cleanup: unlink and close shared memory
    shm_unlink("shared");
    close(fd);

    return 0;
}

