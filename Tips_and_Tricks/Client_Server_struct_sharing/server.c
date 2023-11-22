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

void message_To_Client(int fd){
	struct packet *p = malloc(sizeof(struct packet));
	int len = sizeof(p->message);
	while(1){
		recv(fd, p->message, len, 0);
		if(strcmp("END",p->message) == 0){
			printf("Client is Disconnected...\n");
			return ;
		}

		printf("Message from Client: %s\n",p->message);

		printf("Enter the message: ");
		fgets(p->message, len, stdin);
		p->message[len] = '\0';

		send(fd, p->message, len, 0);
	}
}

int main(int argc, char *args[])
{
	
	int sockfd;
	struct sockaddr_in server,client;
	int len = sizeof(client);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(7020);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&server, len);

	listen(sockfd, 5);
	printf("Server Listening to port 7020....\n");

	int fd = accept(sockfd, (struct sockaddr *)&client, &len);

	message_To_Client(fd);

	close(sockfd);

	return 0;
}