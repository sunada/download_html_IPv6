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
#include <string>

using namespace std;

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in6 dest;

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
    // it's strange for address with '\0' is ok in connect()
    // but not in bind()
    char address1[] = "2001:200:dff:fff1:216:3eff:feb1:44d7";
    //printf("sizeof(address1): %d\n", sizeof(address1));

    //char address1[] = "fe80::201:2ff:fe92:30fb";
    //dest.sin6_port = htons(7838);

    char address[36];
    memcpy(address, address1, sizeof(address1)-1);

    if(inet_pton(AF_INET6, address1, &dest.sin6_addr) < 0){
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

    char requestHeader[] = "GET / HTTP/1.0\r\nHost: www.kame.net\r\n\r\n";

    if(send(sockfd, requestHeader, strlen(requestHeader),0) < 0){
        perror("send");
        exit(errno);
    }
    printf("send successful\n");
    
    char buffer[MAXBUF + 1];
    memset(buffer, 0, MAXBUF+1);
    if(recv(sockfd, buffer, MAXBUF, 0) < 0){
        perror("recv");
        exit(errno);
    }
    printf("receive sucessful\n");

    string respondHeader = string(buffer);
    if(respondHeader.find("HTTP/1.1 200 OK",0) == string::npos){
        perror("failed get");
        return 100;
    }
    printf("recv respond from server\n");
    printf("receid buffer: %s\n", buffer);

    close(sockfd);
    return 0;
}
    
    
