#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/sendfile.h>
int main(int argv, char *argc[])
{
    struct sockaddr_in server;
    int bind_test, lfd, choice, size, filehandle, status;
    char buf[100] = "", sBuf[100] = "", filename[20], *f;
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        printf("socket creation failed");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = atoi(argc[1]);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nClient ready....");
    bind_test = connect(lfd, (struct sockaddr *)&server, sizeof server);
    if (bind_test == -1)
    {
        printf("Connect Error");
        exit(1);
    }
    int i = 1;
    while (1)
    {
        printf("Enter a choice:\n1- get\n2- quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter filename to get: ");
            scanf("%s", filename);
            strcpy(buf, "get");
            strcat(buf, filename);
            send(lfd, buf, 100, 0);
            recv(lfd, &size, sizeof(int), 0);
            if (!size)
            {
                printf("No such file on the remote directory\n\n");
                break;
            }
            f = malloc(size);
            recv(lfd, f, size, 0);
            while (1)
            {
                filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
                if (filehandle == -1)
                {
                    sprintf(filename + strlen(filename), "%d", i);
                    // needed only if same directory is used for both server and client
                }
                else
                    break;
            }
            write(filehandle, f, size, 0);
            close(filehandle);
            strcpy(buf, "cat ");
            strcat(buf, filename);
            system(buf);
            break;
        case 2:
            strcpy(buf, "quit");
            send(lfd, buf, 100, 0);
            recv(lfd, &status, 100, 0);
            if (status)
            {
                printf("Server closed\nQuitting..\n");

                close(lfd);
                exit(0);
            }
            printf("Server failed to close connection\n");
        }
    }
}