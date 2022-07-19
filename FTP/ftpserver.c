#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <stdlib.h>
/*for O_RDONLY*/
#include <fcntl.h>
int main()
{
    struct sockaddr_in client, server;
    struct stat obj;
    int lfd, n, confd, k, size, filehandle;
    char rbuf[100] = "", sBuf[100] = "", filename[20], command[5];
    lfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 3500;
    // server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    k = bind(lfd, (struct sockaddr *)&server, sizeof server);
    if (k == -1)
    {
        printf("Binding error");
        exit(1);
    }
    k = listen(lfd, 1);
    if (k == -1)
    {
        printf("Listen failed");
        exit(1);
    }

    printf("\nServer ready,waiting for client....");
    n = sizeof client;
    confd = accept(lfd, (struct sockaddr *)&client, &n);

    int i = 1;
    while (1)
    {
        recv(confd, rbuf, sizeof rbuf, 0);
        sscanf(rbuf, "%s", command);
        if (!strcmp(command, "get"))
        {
            sscanf(rbuf, "%s%s", filename, filename);
            stat(filename, &obj);
            filehandle = open(filename, O_RDONLY);
            size = obj.st_size;
            if (filehandle == -1)
                size = 0;
            send(confd, &size, sizeof(int), 0);
            if (size)
                sendfile(confd, filehandle, NULL, size);
        }
        else if (!strcmp(command, "bye") || !strcmp(command, "quit"))
        {
            printf("FTP server quitting..\n");
            i = 1;
            send(confd, &i, sizeof(int), 0);
            close(confd);
            close(lfd);
            exit(0);
        }
    }
    return 0;
}