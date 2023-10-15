#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void requestFileToServer(int sockfd);

void requestFileToServer(int sockfd){
	
	char buf[1024];
	FILE *file;
	
	while(1){
		//memset(buf, 0, sizeof(buf));
		printf("Enter your Command: ");
		fgets(buf, sizeof(buf), stdin);
		send(sockfd, buf, sizeof(buf), 0);
		
		if(strncmp(buf, "end\n",5) == 0) {
			printf("Connection closing....\n");
			return ;
		}
		
		if(strncmp(buf, "get ", 4) == 0){
			file = fopen(buf, "w");
			if(file){
				//memset(buf, 0, sizeof(buf));
				recv(sockfd, buf, sizeof(buf), 0);
				fprintf(file, "%s", buf);
				printf("File received Successfully....\n");
				fclose(file);
			}
			else{
				printf("Error in creating file\n");
			}
		}
		else{
			recv(sockfd, buf, sizeof(buf), 0);
			printf("%s\n", buf);
		}
	}
	
	return ;

}

int main(int argc, char *args[])
{
	if(argc < 1){
		printf("No Enough number of arguments\n");
		printf("./FTPserver <path>\n");	
		return 1;
	}
	
	int sockfd;
	struct sockaddr_in client;
	int len = sizeof(client);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	client.sin_family = AF_INET;
	client.sin_port = htons(7020);
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int connecterr = connect(sockfd, (struct sockaddr *)&client, len);
	
	requestFileToServer(sockfd);
	
	close(sockfd);
	
	return 0;
}
