#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_addr()
#include <string.h>
#include <unistd.h>

#define SA struct sockaddr
#define PORT 8080
#define MAX 80

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in serveraddr;
    // 1. Create a TCP Socket
    sockfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (sockfd != 0) {
        printf("Failed to create a socket ...");
        exit(EXIT_FAILURE);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //ToDo: Change this to actual server
    serveraddr.sin_port = htons(PORT);

    // 2. Establish a connection
    connfd = connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr));
    if (connfd != 0) {
        printf("Unable to establish a connection ...");
        exit(0);
    }

    printf("Established connection to server ...");

    // 3. Communicate with the server
    func(sockfd);


    // 4. Close the connection
    close(sockfd);
}
