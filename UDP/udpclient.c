#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main()
{
    struct sockaddr_in server;
    char rbuf[100] = "", sbuf[100] = "";
    int lfd, n;
    lfd = socket(AF_INET, SOCK_DGRAM, 1);
    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("client is ready");
    n = sizeof server;
    while (1)
    {
        printf("\nclient:");
        gets(sbuf);
        sendto(lfd, sbuf, sizeof sbuf, 0, (struct sockaddr *)&server, n);
        if (strcmp(sbuf, "end") == 0)
            break;

        recvfrom(lfd, rbuf, sizeof rbuf, 0, (struct sockaddr *)&server, &n);
        printf("\nserver:%s", rbuf);
        if (strcmp(rbuf, "end") == 0)
            break;
    }
    close(lfd);
}