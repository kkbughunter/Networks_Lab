#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "10.17.202.93"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error: socket");
        exit(1);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Error: inet_pton");
        exit(1);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error: connect");
        exit(1);
    }

    while (1)
    {
        // Send a message to the server
    char message[] = "Hello, Server!";
    if (send(clientSocket, message, strlen(message), 0) < 0) {
        perror("Error: send");
        exit(1);
    }

    // Receive the response from the server
    ssize_t bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytesRead < 0) {
        perror("Error: recv");
        exit(1);
    }

    buffer[bytesRead] = '\0'; // Null-terminate the received data
    printf("Received response from server: %s\n", buffer);

    // Close the client socket
    close(clientSocket);
    }
    

    return 0;
}
