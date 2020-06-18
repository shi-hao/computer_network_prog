#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<time.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>

#define   SERVER_PORT  1195
#define   BUFF_LEN 512
//#define SERVER_IP "192.168.0.129"
#define SERVER_IP "39.105.113.152"
//#define SERVER_IP "127.0.0.1"

void udp_msg_sender(int fd, struct sockaddr* dst)
{
	socklen_t len;
	struct sockaddr_in src;
	while(1)
	{
		char buf[BUFF_LEN] = "TEST UDP MSG!\n";
		len = sizeof(*dst);
		printf("sending:%s\n",buf);  //打印自己发送的信息
		sendto(fd, buf, BUFF_LEN, 0, dst, len);

		memset(buf, 0, BUFF_LEN);
		recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
		printf("recv from [%s:%d]:%s\n",inet_ntoa(src.sin_addr), ntohs(src.sin_port), buf);
		sleep(1);  //一秒发送一次消息
	}
}

/*
client:
socket-->sendto-->revcfrom-->close
 */

int main(int argc, char* argv[])
{
	int client_fd;
	struct sockaddr_in ser_addr;

	printf("\n usage : \n   server ip \n   server port \n   device \n");

	if(argc < 4){
		printf("param is not enough\n");
		exit(0);
	}

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	//---------------------------------------------------------------
#if 0
	//定义sockaddr_in
	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(argv[3]);
	local_addr.sin_port = 0;  //系统随机分配可用port

	//bind成功返回0，出错返回-1
	if(bind(client_fd, (struct sockaddr *)&local_addr,sizeof(local_addr))==-1)
	{
		perror("bind");
		exit(1);//1为异常退出
	}
	printf("bind success.\n");
#endif

#if 1
	/* 
	 * bind the socket to one network device using setsockopt()
	 */
	//const char* device = "wlp4s0";
	const char* device = argv[3];
	int rc;
	rc = setsockopt(client_fd, SOL_SOCKET, SO_BINDTODEVICE, device, strlen(device));
	if (rc != 0)
	{
		perror("setsockopt");
		exit (EXIT_FAILURE);
	}
#endif
	//-------------------------------------------------------------------


	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	//ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
	//ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]); //ip
	ser_addr.sin_port = htons(atoi(argv[2])); //端口号，需要网络序转换

	udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);

	close(client_fd);
	return 0;
}
