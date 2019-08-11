#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "message.h"

int max_sz = MAX_MSG_SIZE;

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    //my code start from here
    int sz;
    if (argc == 2)
    { //message type 2
        sz = atoi(argv[1]);
        msg_2 m;
        m.sz = sz;
        char *p = msg2_pack(&m);
        sz = sizeof(msg) + ((msg *)p)->body_len;
        send(sock, p, sz, 0);
        valread = read(sock, buffer, 1024);
        msg_2 *pp = msg2_unpack(buffer);
        printf("the max message size is:%d next round!\n", pp->sz);
    }
    else
    { //message type 1
        msg_1 m;
        strcpy(m.body, "abc");
        char *p = msg1_pack(&m);
        sz = sizeof(msg) + ((msg *)p)->body_len;
        send(sock, p, sz, 0);
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
    }
    return 0;
}
