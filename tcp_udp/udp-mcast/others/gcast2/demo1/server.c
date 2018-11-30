//服务器实现向多播组发送数据

#include<sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include<memory.h>
#include<stdio.h>

#define MCAST_PORT 8888
#define MCAST_ADDR "224.0.0.88"
int main(int argc,char*argv[]){
	int ret;
	int s;
	int i=1;
	struct sockaddr_in Multi_addr;//多播地址
	struct sockaddr_in client_addr;
	s=socket(AF_INET,SOCK_DGRAM,0);//建立数据报套接字
	if(s<0){
		perror("socket error");
		return -1;
	}
	Multi_addr.sin_family=AF_INET;
	Multi_addr.sin_port=htons(MCAST_PORT);//多播端口
	Multi_addr.sin_addr.s_addr=inet_addr(MCAST_ADDR);//多播地址
	//向多播组发送数据
	char buffer[1024];
	for(;;){
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"%d",i);
		int size=sendto(s,buffer,strlen(buffer),0,(struct sockaddr*)&Multi_addr,sizeof(Multi_addr));
		if(size<0){
			perror("sendto error");
		}
		sleep(1);
		i++;
		memset(buffer,0,sizeof(buffer));
		int len=sizeof(client_addr);
		size=recvfrom(s,buffer,1024,0,(struct sockaddr*)&client_addr,&len);
		write(1,buffer,size);
	}
	close(s);
}
