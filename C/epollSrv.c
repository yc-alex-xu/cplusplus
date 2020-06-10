/*
a simple echo server
$gcc -g epoll.c 
$./a.out
then start multiple telnet to test
$ telnet 127.0.0.1  8000
Trying 127.0.0.1...
Connected to 127.0.0.1.
*/
/* 
epoll的接口非常简单，一共就三个函数：
1. int epoll_create(int size);
创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。需要注意的是，
当创建好epoll句柄后，它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。

2. int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
epoll的事件注册函数
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
操作的类型，具体包含
       EPOLL_CTL_ADD
              Register the target file descriptor fd on the epoll instance
              referred to by the file descriptor epfd and associate the
              event event with the internal file linked to fd.

       EPOLL_CTL_MOD
              Change the event event associated with the target file
              descriptor fd.

       EPOLL_CTL_DEL
              Remove (deregister) the target file descriptor fd from the
              epoll instance referred to by epfd.  The event is ignored and
              can be NULL (but see BUGS below).
events成员变量：
可以是以下几个宏的集合：
EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
EPOLLERR：表示对应的文件描述符发生错误；
EPOLLHUP：表示对应的文件描述符被挂断；
EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。

3. int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，这个 maxevents的值不能大于创建epoll_create()时的size，
参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。该函数返回需要处理的事件数目，如返回0表示已超时。


4、关于ET、LT两种工作模式：
可以得出这样的结论:
ET模式仅当状态发生变化的时候才获得通知,这里所谓的状态的变化并不包括缓冲区中还有未处理的数据,也就是说,如果要采用ET模式,
需要一直read/write直到出错为止,很多人反映为什么采用ET模式只接收了一部分数据就再也得不到通知了,大多因为这样;而LT模式是只要有数据没有处理就会一直通知下去的.
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

#define MAXEVENTS 20
	struct epoll_event events[MAXEVENTS];
	char line[MAXLINE];
	for (;;)
	{
		int nEvents = epoll_wait(epfd, events, MAXEVENTS - 1, 500);

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
				printf("accept client fd=%d\n", fdClient);
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
						epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
						printf("reset from  fd=%d\n", fd);
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
					epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
					printf("FIN from  fd=%d\n", fd);
				}
				else
				{
					line[n] = '\0';
					printf("received data: %s\n", line);

					ev.data.fd = fd;
					ev.events = EPOLLOUT | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
				}
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
