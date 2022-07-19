#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main()
{
    struct sockaddr_in server;
    char sbuf[100] = "", rbuf[100] = "";
    int lfd;

    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("client is ready");
    connect(lfd, (struct sockaddr *)&server, sizeof server);
    while (1)
    {
        printf("\nclient: ");
        gets(sbuf);
        send(lfd, sbuf, sizeof sbuf, 0);
        if (strcmp(rbuf, "end") == 0)
        {
            break;
        }
        recv(lfd, rbuf, sizeof rbuf, 0);
        printf("\nserver:", rbuf);
        if (strcmp(rbuf, "end") == 0)
            break;
        printf("\n");
    }
    close(lfd);
}