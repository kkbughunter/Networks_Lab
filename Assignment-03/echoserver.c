#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

void messageToClient(int fd);

void messageToClient(int fd){

	char buf[1023];
	
	while(1){
		read(fd, buf, sizeof(buf));
		printf("Message Frome Client: %s\n", buf);
		
		if ((strncmp(buf, "exit", 4)) == 0) {
			printf("Server Exit...\n");
			break;
		}
		
		write(fd, buf, sizeof(buf));
	}
	
	return ;
	
}

int main(int argc, char *args[]){
	
	int sockfd;
	struct sockaddr_in server;
	int len = sizeof(server);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = htons(7020);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int binderr = bind(sockfd, (struct sockaddr *)&server, len);
	int listenerr = listen(sockfd, 4);
	printf("Server Listening to port 7020....\n\n");
	int fd = accept(sockfd, (struct sockaddr *)&server, &len);
	printf("%s Client is connect to Server...\n",inet_ntoa(server.sin_addr));
	messageToClient(fd);

	close(sockfd);
}
