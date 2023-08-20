#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error: socket");
        exit(1);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Bind socket to server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error: bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        perror("Error: listen");
        exit(1);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Accept a connection from a client
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Error: accept");
            continue; // Continue listening for other connections
        }

        // Receive data from the client
        ssize_t bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (bytesRead < 0) {
            perror("Error: recv");
            close(clientSocket);
            continue; // Continue listening for other connections
        }

        buffer[bytesRead] = '\0'; // Null-terminate the received data
        printf("Received message from client: %s\n", buffer);

        // Send the received message back to the client
        ssize_t bytesSent = send(clientSocket, buffer, bytesRead, 0);
        if (bytesSent < 0) {
            perror("Error: send");
        }

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket (unreachable in this loop)
    close(serverSocket);

    return 0;
}
