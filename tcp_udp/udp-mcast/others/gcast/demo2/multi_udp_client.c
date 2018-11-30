#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 255
/*********************************************************************
 *filename: mcastclient.c
 *purpose: 演示组播编程的基本步骤，其实这就是一个基本的UDP客户端程序
 *tidied by: zhoulifa(zhoulifa@163.com) 周立发(http://zhoulifa.bokee.com)
 Linux爱好者 Linux知识传播者 SOHO族 开发者 最擅长C语言
 *date time:2007-01-25 13:10:00
 *Note: 任何人可以任意复制代码并运用这些文档，当然包括你的商业用途
 * 但请遵循GPL
 *Thanks to: Google.com
 *Hope:希望越来越多的人贡献自己的力量，为科学技术发展出力
 * 科技站在巨人的肩膀上进步更快！感谢有开源前辈的贡献！
 *********************************************************************/
int main(int argc, char **argv)
{
	struct sockaddr_in peeraddr, myaddr;

	int sockfd;
	char recmsg[BUFLEN + 1];
	unsigned int socklen, n;

	/* 创建 socket 用于UDP通讯 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket creating error\n");
		exit(1);
	}
	socklen = sizeof(struct sockaddr_in);

	/* 设置对方的端口和IP信息 */
	memset(&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	if (argv[2])
		peeraddr.sin_port = htons(atoi(argv[2]));
	else
		peeraddr.sin_port = htons(7838);
	if (argv[1]) {
		/* 注意这里设置的对方地址是指组播地址，而不是对方的实际IP地址 */
		if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0) {
			printf("wrong group address!\n");
			exit(0);
		}
	} else {
		printf("no group address!\n");
		exit(0);
	}


#if 0
	/* 设置自己的端口和IP信息 */
	memset(&myaddr, 0, socklen);
	myaddr.sin_family = AF_INET;
	if (argv[4])
		myaddr.sin_port = htons(atoi(argv[4]));
	else
		myaddr.sin_port = htons(23456);

	if (argv[3]) {
		if (inet_pton(AF_INET, argv[3], &myaddr.sin_addr) <= 0) {
			printf("self ip address error!\n");
			exit(0);
		}
	} else
		myaddr.sin_addr.s_addr = INADDR_ANY;

	/* 绑定自己的端口和IP信息到socket上 */
	if (bind
			(sockfd, (struct sockaddr *) &myaddr,
			 sizeof(struct sockaddr_in)) == -1) {
		printf("Bind error\n");
		exit(0);
	}
#endif 

#if 1
	/* 循环接受用户输入的消息发送组播消息 */
	for (;;) {
		/* 接受用户输入 */
		bzero(recmsg, BUFLEN + 1);
		if (fgets(recmsg, BUFLEN, stdin) == (char *) EOF)
			exit(0);
		/* 发送消息 */
		if (sendto
				(sockfd, recmsg, strlen(recmsg), 0,
				 (struct sockaddr *) &peeraddr,
				 sizeof(struct sockaddr_in)) < 0) {
			printf("sendto error!\n");
			exit(3);
		}
		printf("'%s' send ok\n", recmsg);
	}
#else 
	/* 循环接收网络上来的组播消息 */
	for (;;) {
		bzero(recmsg, BUFLEN + 1);
		n = recvfrom(sockfd, recmsg, BUFLEN, 0,
				(struct sockaddr *) &peeraddr, &socklen);
		if (n < 0) {
			printf("recvfrom err in udptalk!\n");
			exit(4);
		} else {
			/* 成功接收到数据报 */
			recmsg[n] = 0;
			printf("peer:%s", recmsg);
		}
	}
#endif 

}
