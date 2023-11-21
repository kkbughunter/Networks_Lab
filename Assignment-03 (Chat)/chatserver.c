#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void Chat_With_Client(int newfd){
    char buf[1024];
    int len = sizeof(buf);
    while(1){
        recv(newfd, buf, len, 0);

        printf("Data: %s\nEnter the message: ",buf);

        fgets(buf, len, stdin);
        buf[len] = '\0';
        send(newfd, buf, len, 0);

    }
}
int main(int argc, char *args[])
{

    int sockfd, numofclients, newfd;
    struct sockaddr_in server, client;
    int len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(7020);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);

    while(1){
        newfd = accept(sockfd, (struct sockaddr *)&client, &len);

        pid_t client_id = fork();
        if(client_id < 0){
            printf("fork Failed\n");
            close(newfd);
            continue;
        }
        else if(client_id == 0){
            close(sockfd);
            Chat_With_Client(newfd);
            return 0;
        }
        else{
            close(newfd);
        }
    }
    close(sockfd);
    return 0;
}
