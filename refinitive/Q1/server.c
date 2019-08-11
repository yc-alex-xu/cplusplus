#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "message.h"

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    int max_sz = MAX_MSG_SIZE;
    char *buffer = malloc(max_sz);
    char *hello = "Hello e from server";
    func_unpack pf;
    for (;;)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        //here try to read the whole message multiple times
        valread = read(new_socket, buffer, max_sz);
        msg *p = (msg *)buffer;
        int n_left = sizeof(msg) + p->body_len - valread;
        char *p_buf = buffer + valread;
        while (n_left > 0)
        {
            valread = read(new_socket, p_buf, n_left);
            n_left -= valread;
            p_buf += valread;
        }

        switch (p->msg_type)
        {
        case msg_id_1:
            send(new_socket, hello, strlen(hello), 0);
            break;
        case msg_id_2:
            pf = func_unpack_table[p->msg_type];
            msg_2 *pp = pf(buffer);
            max_sz = pp->sz;
            buffer = realloc(buffer, max_sz);
            //send back msg 2 to client, confirm the max message size change
            send(new_socket, buffer, sizeof(msg) + ((msg *)buffer)->body_len, 0);
            break;

        default:
            break;
        }
    }
    return 0;
}