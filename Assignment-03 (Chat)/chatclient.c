#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 7020
#define BUFFER_SIZE 1024


int main()
{
	int client_socket;
	struct sockaddr_in server_config;
	char message[BUFFER_SIZE];
	
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket == -1){
		perror("Socket creation Failed");
		exit(EXIT_FAILURE);
	}
	
	server_config.sin_family = AF_INET;
	server_config.sin_port = htons(PORT);
	server_config.sin_addr.s_addr = inet_addr(SERVER_IP);
	
	if(connect(client_socket,(struct sockaddr *)&server_config, sizeof(server_config)) == -1){
		perror("connection Error");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		printf("Enter the message the send to server:");
		fgets(message, BUFFER_SIZE, stdin);
		
		send(client_socket, message, strlen(message), 0);
		
		recv(client_socket, message, BUFFER_SIZE, 0);
        printf("Server response: %s", message);


        if (strncmp(message, "quit", 4) == 0)
            break;
	
	}
	
	close(client_socket);
	return 0;
}



