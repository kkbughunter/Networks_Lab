#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void messageToClient(int fd);


void messageToClient(int fd){
	FILE *file;
	char buf[1024];
	
	while(1){
		//memset(buf, 0, sizeof(buf));
		recv(fd, buf, sizeof(buf), 0);

		
		if(strncmp(buf, "end\n",5) == 0) {
			printf("Connection closing....\n");
			return ;
		}
		printf("%s\n",buf);
		if(strncmp(buf, "get ",4) == 0){
			char *filename = buf + 4;
			printf("Client Request to File: %s\n", filename);
			file = fopen(filename, "r");
			if(file != NULL){
				fread(buf, 1, sizeof(buf), file);
				fclose(file);
				send(fd, buf, sizeof(buf), 0);
				printf("File served Successfully....\n");
			}
			else{
				send(fd, "File Not Found in Server...\n",17, 0); 
			}
 		}
 		else{
 			send(fd, "Method not allowed..\n", 21, 0);
 		}
	}
	return ;

}

int main(int argc, char *args[])
{

	
	int sockfd;
	struct sockaddr_in server;
	int len = sizeof(server);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = htons(7020);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int binderr = bind(sockfd, (struct sockaddr *)&server, len);
	int listenerr = listen(sockfd, 5);
	printf("Server Listening on port 7020....\n");
	int fd = accept(sockfd, (struct sockaddr *)&server, &len);
	printf("Client %s connected...\n", inet_ntoa(server.sin_addr));
	
	messageToClient(fd);
	
	close(sockfd);
	
	
	
	return 0;
}
