/*
 *udp 服务端单线程（进程）就可以接收多个客户端发来的数据，实现一对多，启动一个服务端，然后启动多个
 *客户端发送数据，服务端可以同时接收到数据，tcp则不可以，tcp通过多线程（进程）实现对多个服务端的响应。
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define SERVER_PORT 9000
#define BUFF_LEN 1024

void handle_udp_msg(int fd)
{
	char buf[BUFF_LEN];  //接收缓冲区，1024字节
	socklen_t len;
	int count;
	struct sockaddr_in client_addr;  //client_addr用于记录发送方的地址信息
	while(1)
	{
		memset(buf, 0, BUFF_LEN);
		len = sizeof(client_addr);
		count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&client_addr, &len);//recvfrom
		if(count == -1)
		{
			printf("recieve data fail!\n");
			return;
		}
		printf("recv:%s\n",buf);  //打印client发过来的信息
		printf("client_addr.sin_addr:%s\n",inet_ntoa(client_addr.sin_addr));  //打印client ip
		printf("client_addr.sin_port:%d\n",ntohs(client_addr.sin_port));  //打印client port

#if 1
		memset(buf, 0, BUFF_LEN);
		sprintf(buf, "hello client, i am server!\n");  //回复client
		sendto(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&client_addr, len);
#endif
	}
}


/*
server:
socket-->bind-->recvfrom-->sendto-->close
 */

int main(int argc, char* argv[])
{
	int server_fd, ret;
	struct sockaddr_in ser_addr; 

	if(argc < 3){
		printf("usage : server_ip  port \n");
		exit(0);
	}

	server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
	if(server_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	//ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址需要进行网络序转换，INADDR_ANY
	//ser_addr.sin_port = htons(SERVER_PORT); //端口号，需要网络序转换
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]); //ip
	ser_addr.sin_port = htons(atoi(argv[2])); //端口号，需要网络序转换

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
		printf("socket bind fail!\n");
		return -1;
	}

	handle_udp_msg(server_fd);   //处理接收到的数据

	close(server_fd);
	return 0;
}
