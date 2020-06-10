/*
a simple echo server
$gcc -g epoll.c 
$./a.out
then start multiple telnet to test
$ telnet 127.0.0.1  8000
Trying 127.0.0.1...
Connected to 127.0.0.1.

*/

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 10
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 8000
#define INFTIM 1000

void setnonblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);

	if (opts < 0)
	{
		perror("fcntl(sock, GETFL)");
		exit(1);
	}

	opts = opts | O_NONBLOCK;

	if (fcntl(sock, F_SETFL, opts) < 0)
	{
		perror("fcntl(sock, SETFL, opts)");
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	int fdSrv = socket(AF_INET, SOCK_STREAM, 0);
	setnonblocking(fdSrv);

	//add a event
	struct epoll_event ev;
	ev.data.fd = fdSrv;
	ev.events = EPOLLIN | EPOLLET;
	int epfd = epoll_create(256);
	epoll_ctl(epfd, EPOLL_CTL_ADD, fdSrv, &ev);

	//server address
	struct sockaddr_in serveraddr;
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	char *local_addr = "127.0.0.1";
	inet_aton(local_addr, &(serveraddr.sin_addr));
	serveraddr.sin_port = htons(SERV_PORT);

	bind(fdSrv, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	listen(fdSrv, LISTENQ);
	printf("epoll echo server listending on port %d \n", SERV_PORT);

	struct epoll_event events[20];
	char line[MAXLINE];
	for (;;)
	{
		int nEvents = epoll_wait(epfd, events, 20, 500);

		for (int i = 0; i < nEvents; ++i)
		{
			if (events[i].data.fd == fdSrv)
			{
				struct sockaddr_in clientaddr;
				socklen_t clilen;
				int fdClient = accept(fdSrv, (struct sockaddr *)&clientaddr, &clilen);
				if (fdClient < 0)
				{
					perror("fdClient < 0");
					exit(1);
				}
				printf("accept connection fd=%d\n", fdClient);
				setnonblocking(fdClient);

				char *str = inet_ntoa(clientaddr.sin_addr);
				printf("connect from %s\n", str);

				//add socket of new connection
				ev.data.fd = fdClient;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, fdClient, &ev);
			}
			else if (events[i].events & EPOLLIN)
			{
				int fd = events[i].data.fd;
				if (fd < 0)
					continue;
				ssize_t n = read(fd, line, MAXLINE);	
				if (n < 0)
				{
					if (errno == ECONNRESET)
					{
						close(fd);
						events[i].data.fd = -1;
					}
					else
					{
						printf("readline error");
					}
				}
				else if (n == 0)
				{
					close(fd);
					events[i].data.fd = -1;
				}
				line[n]='\0';
				printf("received data: %s\n", line);

				ev.data.fd = fd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
			}
			else if (events[i].events & EPOLLOUT)
			{
				int fd = events[i].data.fd;
				write(fd, line, strlen(line));

				printf("written data: %s\n", line);

				ev.data.fd = fd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
			}
		}
	}
}
