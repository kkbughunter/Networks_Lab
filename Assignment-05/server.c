#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void Message_to_Client(int newfd){
	char buf[1024], sip[] = "127.0.0.3",dip[] = "127.0.0.4",smac[] = "ABC";
	int size = sizeof(buf);
	while(1){
		recv(newfd, buf, size, 0);
		printf("Client: %s\n", buf);

		if(strcmp(dip,buf) == 0){
			send(newfd, "Success\n", size, 0);
		}
		else{
			send(newfd, " ", size, 0);
		}
		
		
	}
	return ;
}

int main(int argc, char *args[])
{
	int sockfd, newfd;
	struct sockaddr_in server, client;
	int len = sizeof(client);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(7020);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&server, len);

	listen(sockfd, 5);
	printf("Server listening at port 7020....\n");

	while(1){
		newfd = accept(sockfd, (struct sockaddr *)&client, &len);

		pid_t childid = fork();

		if(childid < 0){
			printf("Fork Failde...\n");
			close(newfd);
			continue;
		}
		else if(childid == 0){
			close(sockfd);
			Message_to_Client(newfd);
			return 0;
		}
		else{
			close(newfd);
		}
	}
	return 0;
}
