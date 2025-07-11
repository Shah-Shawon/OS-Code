// client.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Create socket
    int client = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address (same port as server)
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;   // Localhost or same machine

    // Connect to the server
    connect(client, (struct sockaddr*)&addr, sizeof(addr));

    // Send message to server
    write(client, "Hello from client", 18);

    // Read server response
    char buffer[100] = {0};
    read(client, buffer, sizeof(buffer));

    printf("Received from server: %s\n", buffer);

    // Close the connection
    close(client);

    return 0;
}