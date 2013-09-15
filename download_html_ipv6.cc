/*********************discription*************************
*filename: download_html_ipv6.cc
*purpose: connects to an IPv6 website, downloads the first page of html or the robots.txt of the website.
*author: Ada Sun
*date: 2013/08/14
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_in6 dest;
    char buffer[MAXBUF + 1];

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
        perror("Socket");
        exit(errno);
    }
    printf("socket created\n");

    //bzero is used in linux
    bzero(&dest, sizeof(dest));
    //memset(&dest, 0, sizeof(dest));

    dest.sin6_family = AF_INET6;
    dest.sin6_port = htons(80);
    char address1[] = "2001:200:dff:fff1:216:3eff:feb1:44d7";
    printf("sizeof(address1): %d\n", sizeof(address1));

    //char address1[] = "fe80::201:2ff:fe92:30fb";
    //dest.sin6_port = htons(7838);

    char address[36];
    memcpy(address, address1, sizeof(address1)-1);

    if(inet_pton(AF_INET6, address, &dest.sin6_addr) < 0){
        perror("inet_pton");
        exit(errno);
    }
    printf("dest address created\n");

    //test whether the IPv6 address is right
    //memset(buffer, '0', sizeof(buffer));
    //inet_ntop(AF_INET6, &dest.sin6_addr, buffer, INET6_ADDRSTRLEN);
    //printf("dest.sin6_addr: %s\n", buffer);
    //printf("dest.port: %d\n", ntohs(dest.sin6_port));


    if(connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0){
        perror("Connect");
        exit(errno);
    }
    printf("server connected\n");

    close(sockfd);
    return 0;
}
    
    
