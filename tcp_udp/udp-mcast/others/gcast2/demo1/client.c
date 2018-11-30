#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
//多播的客户端程序
#define PORT 8888
#define MCAST "224.0.0.88"
int main(int argc,char*argv[]){
	int s;
	int ret;
	int size;
	int ttl=10;//如果转发的次数等于10,则不再转发
	int loop=0;
	int times=0;
	char buffer[1024];
	struct sockaddr_in localaddr,fromaddr;//多播地址结构
	//建立套接字
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s<0){
		perror("socket error");
		return -1;
	}
	//多播的地址结构
	localaddr.sin_family=AF_INET;
	localaddr.sin_port=htons(PORT);//多播端口号
	localaddr.sin_addr.s_addr=htonl(INADDR_ANY);//接收任意地址发送的数据
	//绑定地址结构到套接字
	ret=bind(s,(struct sockaddr*)&localaddr,sizeof(localaddr));//客户端需要绑定端口，用来接收服务器的数据，得指定接收端口，因为数据先从服务器发送过来的
	if(ret<0){
		perror("bind error");
		return -1;
	}
	//设置多播的TTL值
	if(setsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL,&ttl,sizeof(ttl))<0){
		perror("IP_MULTICAST_TTL");
		return -1;
	}

	//设置数据是否发送到本地回环接口
	if(setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop))<0){
		perror("IP_MULTICAST_LOOP");
		return -1;
	}
	//客户端加入多播组
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr(MCAST);//多播组的IP
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);//本机的默认接口IP
	if(setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0){
		perror("IP_ADD_MEMBERSHIP");
		return -1;
	}
	//循环接收多播组的消息，5次退出
	for(times=0;times<20;times++){
		int len=sizeof(fromaddr);
		memset(buffer,0,sizeof(buffer));
		size=recvfrom(s,buffer,1024,0,(struct sockaddr*)&fromaddr,&len);
		if(size<0){
			perror("recvfrom ");
			return -1;
		}
		printf("receive message:%s\n",buffer);
		printf("Port is:%d\n",fromaddr.sin_port);
		size=sendto(s,"OK",2,0,(struct sockaddr*)&fromaddr,sizeof(fromaddr));//向服务器发送数据,向服务器指定的IP与端口发送数据
	}

	//离开多播组
	ret=setsockopt(s,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq));
	if(ret<0){
		perror("IP_DROP_MEMBERSHIP");
		return -1;
	}
	close(s);
	return 0;

}
