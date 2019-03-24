#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<time.h>
#include<unistd.h>
#include <arpa/inet.h>

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
#if 1
		len = sizeof(*dst);
		printf("client:%s\n",buf);  //打印自己发送的信息
		sendto(fd, buf, BUFF_LEN, 0, dst, len);
		memset(buf, 0, BUFF_LEN);
#endif
#if 0
		struct sockaddr_in dst_addr;
		int ret;
		dst_addr.sin_family = AF_INET;
		dst_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
		//ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
		//printf("%d\n",INADDR_ANY);
		dst_addr.sin_port = htons(9000);  //注意网络序转换

		ret = bind(fd, (struct sockaddr*)&dst_addr, sizeof(dst_addr));
		if(ret < 0) printf("bind error\n");
#endif
#if 1
		recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
		printf("server:%s\n",buf);
#endif
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

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
	//printf("%d\n",INADDR_ANY);
	ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换

	udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);

	close(client_fd);

	return 0;
}
