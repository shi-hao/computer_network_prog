/*
 * udp 服务端单线程（进程）就可以接收多个客户端发来的数据，实现一对多，启动一个服务端，然后启动多个
 * 客户端发送数据，服务端可以同时接收到数据，tcp则不可以，tcp的通过多线程（进程）实现对多个服务端的响应。
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
	struct sockaddr_in clent_addr;  //clent_addr用于记录发送方的地址信息
	while(1)
	{
		memset(buf, 0, BUFF_LEN);
		len = sizeof(clent_addr);
		//recvfrom是拥塞函数，没有数据就一直拥塞
		count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len);  
		if(count == -1)
		{
			printf("recieve data fail!\n");
			return;
		}
		printf("client:%s\n",buf);  //打印client发过来的信息
		printf("clent_addr.sin_addr:%s\n",inet_ntoa(clent_addr.sin_addr));  //打印client ip
		printf("clent_addr.sin_port:%d\n",clent_addr.sin_port);  //打印client port

#if 1
		memset(buf, 0, BUFF_LEN);
		sprintf(buf, "I have recieved %d bytes data!\n", count);  //回复client
		//printf("server:%s\n",buf);  //打印自己发送的信息给
        //发送信息给client，注意使用了clent_addr结构体指针
		sendto(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, len);  
		sleep(1);
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

	server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
	if(server_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
	ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
		printf("socket bind fail!\n");
		return -1;
	}

#if 1
	handle_udp_msg(server_fd);   //处理接收到的数据
#else
	struct sockaddr_in peer_addr;
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	peer_addr.sin_port = htons(9000);
	char buf[]="i am udp server";
	for(;;){
		sendto(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
		//sendto(server_fd, buf, sizeof(buf), 0, NULL, 0);
		printf("%s\n", buf);
		sleep(1);
	}
#endif

	close(server_fd);
	return 0;
}
