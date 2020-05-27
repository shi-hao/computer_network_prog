#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include<time.h>

#define BUFLEN 255
#define buf_len 40
/*********************************************************************
 *
 *   组播ip， 端口号，  接收组播数据网卡
 *
 *********************************************************************/

int main(int argc, char **argv)
{
	struct sockaddr_in multicast_addr, from_addr;
	int sockfd;
	char recmsg[BUFLEN + 1];
	unsigned int socklen, n;
	char from_ip[buf_len];

	//组播地址结构
	struct ip_mreq mreq;

	/* 创建 socket 用于UDP通讯 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket creating err\n");
		exit(1);
	}

	//----------------------------------------------------------
	//配置socket用于接收组播数据
	//truct sockaddr_in
	//sockaddr_in.sin_family 
	//sockaddr_in.sin_port   接收数据的端口，此处为组播端口
	//sockaddr_in.sin_addr   组播地址
	//bind  将socket和地址绑定
#if 1
	memset(&multicast_addr, 0, sizeof(struct sockaddr_in));
	multicast_addr.sin_family = AF_INET;
	if (argv[2])
		multicast_addr.sin_port = htons(atoi(argv[2]));
	else
		multicast_addr.sin_port = htons(7838);
	//multicast_addr.sin_addr.s_addr = inet_addr("230.1.1.88");
	if (argv[1]) {
		if (inet_pton(AF_INET, argv[1], &multicast_addr.sin_addr.s_addr) <= 0) {
			printf("Wrong dest IP address!\n");
			exit(0);
		}
	} else {
		printf("you should give me a group address, 224.0.0.0-239.255.255.255\n");
		exit(0);
	}

	/* 绑定组播端口和IP信息到socket上 */
	if (bind(sockfd, (struct sockaddr *)&multicast_addr, sizeof(struct sockaddr_in)) == -1) {
		printf("Bind error\n");
		exit(0);
	}
#endif

	/* 加入组播 
	 * struct ip_mreq
	 * ip_mreq.imr_multiaddr.s_addr   设置要加入的组播地址 
	 * ip_mreq.imr_interface.s_addr   设置将哪个网卡加入组播地址，使用netstat -gn可以查看是否成功加入
	 * setsockopt()                   将设置写入系统配置
	 */
	bzero(&mreq, sizeof(struct ip_mreq));
	if (argv[1]) {
		if (inet_pton(AF_INET, argv[1], &mreq.imr_multiaddr.s_addr) <= 0) {
			printf("Wrong dest IP address!\n");
			exit(0);
		}
	} else {
		printf("you should give me a group address, 224.0.0.0-239.255.255.255\n");
		exit(0);
	}

	if (argv[3]) {
		if (inet_pton(AF_INET, argv[3], &mreq.imr_interface.s_addr) <= 0) {
			printf("Wrong dest IP address!\n");
			exit(0);
		}
	} else {
		printf("you should give me a local net card address\n");
		exit(0);
	}

	/* 把本机加入组播地址，即本机网卡作为组播成员，只有加入组才能收到组播消息 */
	//IP_ADD_MEMBERSHIP, 告知内核，接收组播数据，内核默认丢弃
	//IP_DROP_MEMBERSHIP，告知内核，丢弃组播数据
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1) {
		perror("setsockopt");
		exit(-1);
	}
#if 0
	//设置接收回环许可，即可以接收本地网卡的组播数据
	int loop = 1;
	if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0)
		printf("setsockopt IP_MULTICAST_LOOP error!\n");
#endif


	time_t rawTime;
	struct tm* timeinfo;
	char strTime[50]={0};



	/* 循环接收网络上来的组播消息 */
	socklen = sizeof(from_addr);
	int times=0;
	for (;;) {
		times++;
		bzero(recmsg, BUFLEN + 1);
		n = recvfrom(sockfd, recmsg, BUFLEN, 0,(struct sockaddr *) &from_addr, &socklen);
		if (n < 0) {
			printf("recvfrom err!\n");
			exit(4);
		} else {
			time(&rawTime);
			timeinfo = localtime(&rawTime);
			sprintf(strTime, " %4d-%02d-%02d %02d:%02d:%02d ",
					1900+timeinfo->tm_year,
					1+timeinfo->tm_mon,
					timeinfo->tm_mday,
					timeinfo->tm_hour,
					timeinfo->tm_min,
					timeinfo->tm_sec);
			/* 成功接收到数据报 */
			printf(" %s Recv num %d multicast data from ip %s:%s\n", strTime,times, 
					inet_ntop(AF_INET, &from_addr.sin_addr.s_addr, from_ip, buf_len),
					recmsg);
		}
	}
}
