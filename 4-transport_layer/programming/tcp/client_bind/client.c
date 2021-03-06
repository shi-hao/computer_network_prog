/*
 * 绑定TCP Socket IP地址和端口号
 *
 * 1.bind函数作用
 *   将socket和指定的IP地址和端口号进行绑定，让socket在绑定的地址上收发数据，即
 * 发送数据时，IP包的源地址TCP的源端口使用指定的地址，接收数据时，只接收目的IP
 * 地址和目的端口号匹配的数据包。
 * bind函数参数中的IP地址必须是主机本地网卡的地址或者设置为全0,表示是本地任意一
 * 个网卡地址。
 *
 * 2.TCP Client绑定IP地址和端口号
 *   一般情况下，在使用TCP通信时，客户端一般不需要指定使用的IP地址和端口号，
 * 而是由系统内核统一分配，主要有以下两点好处。
 * (1)简化使用TCP的流程，编程更简单。
 * (2)IP地址和端口号由系统内核统一分配，可以避免端口冲突，如果所有的TCP连
 * 接都需要用户指定端口号，可能会导致冲突，因为系统内一般有好多进程在使用TCP通
 * 信，不同的进程预先指定了端口号，那么很有可能不同进程预先设定了相同的端口号
 * 而造成冲突。
 *   虽然TCP客户端指定源IP地址和源端口号并不推荐，但是软件接口支持这种操作，使用
 * bind接口即可实现。
 *
 * 3.为什么TCP服务端必须指定IP地址和端口号
 *   CS模式，Server首先要处在被动打开状态，所以server要主动在指定的IP地址
 * 和端口号下监听数据，所以必须要进行绑定操作。
 *
 */
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

	//定义IPV4的TCP连接的套接字描述符
	int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

#if 1
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
