#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd;
    int new_fd;
    unsigned int myport = 7838;
    unsigned int lisnum = 2;

    socklen_t len;

    struct sockaddr_in6 addr;
    struct sockaddr_in6 client_addr;
    char buf[MAXBUF + 1];
    
    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(errno);
    }
    printf("socket created\n");

    //memset(&addr, 0, sizeof(addr));
    bzero(&addr, sizeof(addr));

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(myport);
    //it's strange for address with '\0' is ok in connect(),
    // but not in bind()
    char addrstr1[] = "fe80::201:2ff:fe92:30fb";
    char addrstr[23];
    memcpy(addrstr,addrstr1,sizeof(addrstr1)-1);

    inet_pton(AF_INET6, addrstr, &addr.sin6_addr);

    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6)) == -1){
        perror("bind");
        exit(errno);
    }
    printf("bind succeed\n");

    if(listen(sockfd, 2) == -1){
        perror("listen");
        exit(errno);
    }
    printf("listen succeed\n");

    while(1){
        len = sizeof(struct sockaddr);
        if((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &len)) == -1){
            perror("accept");
            exit(errno);
        }
        printf("accept succeed. connected from %s, port %d, socket %d\n", inet_ntop(AF_INET6, &client_addr.sin6_addr, buf, sizeof(buf)), client_addr.sin6_port, new_fd);
    }
    close(sockfd);
    return 0;
}
