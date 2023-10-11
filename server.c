#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAX 80
#define PORT 8080
#define QUEUELIMIT 5
#define SA struct sockaddr

int main() {
    int sockfd, connfd, status;
    struct sockaddr_in servaddr, cli;

    // create socket and verify
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Failed creating socket ...\n");
        exit(0);
    }
    printf("Socket is successfully created ...\n");


    // specify the address and port for the socket
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);

    // bind can be skipped
    status = bind(sockfd, (SA*) &servaddr, sizeof(servaddr));
    if (status != 0) {
        printf("Unable to bind to socket ...\n");
        exit(0);
    }
    printf("Socket successfully bound ...\n");

    status = listen(sockfd, QUEUELIMIT);
    if (status != 0) {
        printf("Unable to connect to the port ...\n");
        exit(0);
    }
    printf("Socket is listening for packets on localhost:8080...\n");

    connfd = accept(sockfd, (SA*)&cli, (socklen_t*) &cli.sin_len);
    if (connfd < 0) {
        printf("Unable to accept connections ...\n");
        exit(0);
    }
    printf("server is ready to accept connections ...\n");

    // We should be able to change the port
    status = listen(sockfd, 5);
    if (status != 0) {
        printf("Unable to listen to the port ...\n");
        exit(1);
    }


    // close the docket once the server stops working
    status = close(sockfd);
    if (status == -1) {
        printf("Unable to close socket connection ...\n");
        exit(1);
    }

}
