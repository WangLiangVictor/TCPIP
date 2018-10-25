#include <sys/types.h>
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h> 

#define SERVPORT 3333 

int main()
{
    struct sockaddr_in server_sockaddr = {0}, client_sockaddr = {0};
    int recvbytes = 0, num = 0;
    socklen_t sin_size = {0};
    int sockfd = 0, client_fd = 0;
    char buf[100] = {0};

    /*建立socket连接*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    printf("socket success! sockfd=%d\n", sockfd);

    /*设置sockaddr_in结构体中相关参数*/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(SERVPORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);

    /*绑定函数bind*/
    if(bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    printf("bind success!\n");

    /*调用listen函数*/
    if(listen(sockfd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("listening....\n");


    sin_size = sizeof(client_sockaddr);
    /*调用accept函数，等待客户端的连接*/
    if((client_fd = accept(sockfd, (struct sockaddr *)&client_sockaddr, &sin_size)) == -1)
    {
        perror("accept");
        exit(1);
    }

    while(1)
    {
        /*调用recv函数接收客户端的请求*/
        memset(buf, 0, sizeof(buf));
        if((recvbytes = recv(client_fd, buf, 100, 0)) == -1)
        {
            perror("recv");
            exit(1);
        }
        
        else if(recvbytes == 0)
        {
            continue;
        }

        else
        {
            printf("received a connection no.%d: %s\n", num, buf);
            num++;
        }
    }

    close(sockfd);
}
