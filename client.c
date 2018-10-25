#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 

#define SERVPORT 3333 

int main(int argc, char *argv[])
{
    int sockfd = 0, sendbytes = 0, num = 0;
    char buf[100] = {0};
    struct hostent *host = NULL;
    struct sockaddr_in serv_addr = {0};

    if(argc < 2)
    {
        fprintf(stderr, "Please enter the server's hostname!\n");
        exit(1);
    }

    /*地址解析函数*/
    if((host = gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    /*创建socket*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    /*设置sockaddr_in结构体中相关函数*/
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVPORT);
    serv_addr.sin_addr = *((struct in_addr*)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    /*调用connect函数主动发起对服务器端的连接*/
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    while(1)
    {
        /*发送消息给服务器端*/
        memset(buf, 0, sizeof(buf));
        printf("Please enter a string no.%d:", num);
        scanf("%s", buf);
        if((sendbytes = send(sockfd, buf, strlen(buf), 0)) == -1)
        {
            perror("send");
            exit(1);
        }
        num++;
    }

    close(sockfd);
} 
