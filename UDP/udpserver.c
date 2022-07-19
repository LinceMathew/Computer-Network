#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

void main()
{
    struct sockaddr_in client, server;

    int lfd, n;
    char rbuf[100] = "", sbuf[100] = "";
    lfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 2001;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(lfd, (struct sockaddr *)&server, sizeof server);
    printf("\nServer ready,waiting for client....");
    n = sizeof client;
    while (1)
    {
        recvfrom(lfd, rbuf, sizeof rbuf, 0, (struct sockaddr *)&client, &n);
        printf("\nclient:%s", rbuf);
        if (strcmp(rbuf, "end") == 0)
            break;

        printf("\nserver:");
        gets(sbuf);
        sendto(lfd, sbuf, sizeof sbuf, 0, (struct sockaddr *)&client, n);
        if (strcmp(sbuf, "end") == 0)
            break;
    }
    close(lfd);
}