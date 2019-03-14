#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in myaddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);  //获得fd

	bzero(&myaddr,sizeof(myaddr));  //初始化结构体
	myaddr.sin_family = AF_INET;    //设置地址家族
	myaddr.sin_port = htons(800);   //设置端口
	myaddr.sin_addr.s_addr = inet_addr("192.168.1.10");  //设置地址
	bind(sockfd,(struct sockaddr *)&myaddr, sizeof(struct sockaddr));/*bind的时候进行转化*/


	printf("myaddr.sin_addr = %s\n", inet_ntoa(myaddr.sin_addr));
	printf("myaddr.sin_port = %d\n", ntohs(myaddr.sin_port));
	return 0;
}
