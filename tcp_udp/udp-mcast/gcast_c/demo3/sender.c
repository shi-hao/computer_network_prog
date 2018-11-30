#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFLEN 255

/*********************************************************************
 *
 *  ./sender  group_address   group_port 
 *
 *********************************************************************/

#define sleep_time   2

int main(int argc, char **argv)
{
	struct sockaddr_in group_addr;
	int packet_id=0;

	int sockfd;
	char buffer[50];
	unsigned int socklen;

	/* 创建 socket 用于UDP通讯 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket creating error\n");
		exit(1);
	}
	socklen = sizeof(struct sockaddr_in);

	//--------------------------------------------------------------------------
	/* 设置组播地址和端口 */
	memset(&group_addr, 0, socklen);
	group_addr.sin_family = AF_INET;
	if (argv[2])
		group_addr.sin_port = htons(atoi(argv[2]));
	else
		group_addr.sin_port = htons(7838);
	if (argv[1]) {
		if (inet_pton(AF_INET, argv[1], &group_addr.sin_addr) <= 0) {
			printf("wrong group address!\n");
			exit(0);
		}
	} else {
		printf("no group address!\n");
		exit(0);
	}


#if 1
	//设置发送的组播包的ttl
	int ttl = 1;
	setsockopt(sockfd,IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
#endif

	for (;;) {
		packet_id++;
		sprintf(buffer,"multicast test data %d", packet_id); 
		int n = sendto(sockfd,                           /*套接字描述符*/
				buffer,     /*数据*/
				sizeof(buffer),    /*长度*/
				0,
				(struct sockaddr*)&group_addr, //组播地址结构
				sizeof(group_addr)) ;
		if( n < 0)
		{
			perror("sendto()");
			return -2;
		}      
		sleep(sleep_time);                          /*等待一段时间*/
	}
}
