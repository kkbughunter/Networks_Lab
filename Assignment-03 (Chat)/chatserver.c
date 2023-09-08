#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h>

#define PORT 7020
#define BUFFER_SIZE 1024

int main(int argv, char *argc[])
{
	int server_socket;
	int client_socket;
	struct sockaddr_in server_config;
	struct sockaddr_in client_config;
	socklen_t addr_len = sizeof(client_config);
	char buffer[BUFFER_SIZE];
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0); 
	if(server_socket == -1){
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}
	
	server_config.sin_family = AF_INET;   // which indicates that the socket will be used for IPv4 communication.
	server_config.sin_port = htons(PORT); // he htons function is used to convert the port number from host byte order to network byte order
	server_config.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY, indicating that the socket will bind to all available network interfaces
	
	if(bind(server_socket,(struct sockaddr *)&server_config, sizeof(server_config)) == -1){
		perror("Binding Failed");
		exit(EXIT_FAILURE);
	}
	
	if(listen(server_socket, 5) == -1){
		perror("Listening Failed");
		exit(EXIT_FAILURE);
	}
	
	printf("Server Listening on prot %d\n\n", PORT);
	
	
	while(1){
		
		client_socket = accept(server_socket, (struct sockaddr *)&client_config, &addr_len);
		if(client_socket == -1){
			perror("Error in accepting connection");
			exit(EXIT_FAILURE);
		}
		
		int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (bytes_received == -1) {
            perror("Receiving failed");
            exit(EXIT_FAILURE);
        }
        
        buffer[bytes_received] = '\0';
        // only change is hear
        printf("Client: %s", buffer);
        
        printf("Server (message to send): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);
        
        close(client_socket);
	}
	
	
	
	close(server_socket);
	
	return 0;
}



