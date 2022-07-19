#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{

    struct sockaddr_in client, server;
    int lfd, confd, n, bd;
    char rbuf[100] = "", sbuf[100] = "";

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 2000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(lfd, (struct sockaddr *)&server, sizeof server);
    listen(lfd, 1);
    printf("%d\n%d", lfd, bd);
    printf("server ready waiting for client");
    n = sizeof client;
    confd = accept(lfd, (struct sockaddr *)&client, &n);
    while (1)
    {
        recv(confd, rbuf, sizeof rbuf, 0);
        printf("\nclient:%s", rbuf);
        if (strcmp(rbuf, "end") == 0)
            break;
        printf("\nserver:");
        gets(sbuf);
        send(confd, sbuf, sizeof sbuf, 0);
        if (strcmp(sbuf, "end") == 0)
            break;
    }
    close(confd);
    close(lfd);
    return 0;
}