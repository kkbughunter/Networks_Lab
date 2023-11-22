#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct packet{
	int frameid;
	char message[255];
};

void message_To_Server(int fd){
	struct packet *p = malloc(sizeof(struct packet));
	int len = sizeof(p->message);
	while(1){
		printf("Enter the message: ");
		fgets(p->message, len, stdin);
		p->message[len] = '\0';

		send(fd, p->message, len, 0);

		if(strcmp("END",p->message) == 0){
			printf("Server is Disconnected...\n");
			return ;
		}

		recv(fd, p->message, len, 0);
		printf("Message from Server: %s\n",p->message);
	}
}

int main(int argc, char *args[])
{
	
	int sockfd;
	struct sockaddr_in client;
	int len = sizeof(client);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	client.sin_family = AF_INET;
	client.sin_port = htons(7020);
	client.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&client, len);

	connect(sockfd, (struct sockaddr *)&client, len);

	message_To_Server(sockfd);

	close(sockfd);

	return 0;
}