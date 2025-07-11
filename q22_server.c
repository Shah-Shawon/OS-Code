// server_single.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Create socket: TCP (SOCK_STREAM)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);          // Port 8080
    addr.sin_addr.s_addr = INADDR_ANY;    // Any local IP

    // Bind socket to the IP/Port
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    // Start listening (backlog 5)
    listen(sockfd, 5);
    printf("Server started. Listening on port 8080...\n");

    // Accept and handle clients one at a time
    while (1) {
        int new_sock = accept(sockfd, NULL, NULL);   // Accept new connection
        char buffer[100] = {0};

        // Read data from the client
        read(new_sock, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);

        // Send response back
        write(new_sock, "Hello from server", 18);

        // Close client socket
        close(new_sock);
    }

    return 0;
}