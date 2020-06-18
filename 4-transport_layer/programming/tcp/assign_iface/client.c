#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define PORT  8890
#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		printf("\n usage: server_ip port local_ip \n");
		exit(0);
	}

	//定义IPv4的TCP连接的套接字描述符
	int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

	//---------------------------------------------------------------
#if 0
	//定义sockaddr_in
	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(argv[3]);
	local_addr.sin_port = 0;  //系统随机分配可用port

	//bind成功返回0，出错返回-1
	if(bind(sock_cli,(struct sockaddr *)&local_addr,sizeof(local_addr))==-1)
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
	//const char* device = "eno1";
	const char* device = "wlxec3dfde15940";
	int rc;
	rc = setsockopt(sock_cli, SOL_SOCKET, SO_BINDTODEVICE, device, strlen(device));
	if (rc != 0)
	{
		perror("setsockopt");
		exit (EXIT_FAILURE);
	}
#endif
	//-------------------------------------------------------------------

	//定义sockaddr_in
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));  //服务器端口

	//连接服务器，成功返回0，错误返回-1
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}
	printf("connect to server(IP:%s).\n",argv[1]);

	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	//客户端将控制台输入的信息发送给服务器端，服务器原样返回信息
	while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
		if(strcmp(sendbuf,"exit\n")==0)
		{
			printf("client exited.\n");
			break;
		}
		recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
		printf("client receive: %s \n", recvbuf);

		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}

	close(sock_cli);
	return 0;
}
