// q21.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Global variables
int* fib;     // Pointer to dynamically allocated Fibonacci array
int n;        // Number of terms in the series

// Thread function to generate Fibonacci series
void* generate_fib() {
    fib[0] = 0;
    if (n > 1)
        fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    // Check for required command line argument
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    // Convert input to integer
    n = atoi(argv[1]);

    // Allocate memory for Fibonacci series
    fib = malloc(sizeof(int) * n);
    if (fib == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Create and run thread
    pthread_t thread;
    pthread_create(&thread, NULL, generate_fib, NULL);
    pthread_join(thread, NULL);

    // Print generated Fibonacci series
    printf("Fibonacci series:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    // Free allocated memory
    free(fib);
    return 0;
}