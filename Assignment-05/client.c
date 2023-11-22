#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void Message_to_Server(int newfd){
	char buf[1024];
	int size = sizeof(buf);
	while(1){
		printf("Message: ");
		scanf("%s", buf);
		send(newfd, buf, size, 0);
		
		recv(newfd, buf, size, 0);
		printf("Client: %s\n", buf);		
	}
	return ;
}

int main(int argc, char *args[])
{
	int sockfd, newfd;
	struct sockaddr_in client;
	int len = sizeof(client);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	client.sin_family = AF_INET;
	client.sin_port = htons(7020);
	client.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&client, len);

	connect(sockfd, (struct sockaddr *)&client, len);

	Message_to_Server(sockfd);
	
	return 0;
}
