#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void messageToServer(int sockfd);

void messageToServer(int sockfd){
	
	char buf[1023];
	
	for(;;){
		printf("Enter the message to send: ");
		fgets(buf, 1023, stdin);
		buf[sizeof(buf)-1] = '\0';
		
		write(sockfd, buf, sizeof(buf)); 
		
		if ((strncmp(buf, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
		
		read(sockfd, buf, sizeof(buf));
		printf("Message Frome Server: %s\n", buf);
	}
}

int main(int argc, char *args[]){

	int sockfd;
	struct sockaddr_in client;
	int len = sizeof(client);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	client.sin_family = AF_INET;
	client.sin_port = htons(7020);
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int binderr = bind(sockfd, (struct sockaddr *)&client, len);
	
	int connecterr = connect(sockfd, (struct sockaddr *)&client, len);
	
	messageToServer(sockfd);
	
	return 0;
}
