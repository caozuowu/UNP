#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY 用任意网络接口
	servaddr.sin_port        = htons(13);	/* daytime server */

    //绑定套接字和server地址
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    //调用listen函数把该套接字转换成一个监听套接字，这样来自客户的外来连接就可在该套接字上由内核接受。
	Listen(listenfd, LISTENQ);

    //socket、bind和listen这3个调用步骤是任何TCP服务器准备所谓的监听描述符

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        char logbuffer[1024];
        snprintf(logbuffer, sizeof(logbuffer), "%.24s %s", ctime(&ticks), "return time");
        fprintf(stdout, "%s", logbuffer);
        
        Write(connfd, buff, strlen(buff));

		Close(connfd);
	}
}
