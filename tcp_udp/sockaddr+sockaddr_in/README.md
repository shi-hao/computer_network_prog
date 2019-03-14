struct sockaddr和struct sockaddr_in这两个结构体用来处理网络通信的地址。  
一、sockaddr  
sockaddr在头文件#include <sys/socket.h>中定义，sockaddr的缺陷是：sa_data把目标地址和端口信息混在一起了，如下：  
  
struct sockaddr {    
	sa_family_t sin_family;//地址族  
　  char sa_data[14]; //14字节，包含套接字中的目标地址和端口信息                 
};   
  
二、sockaddr_in  
sockaddr_in在头文件#include<netinet/in.h>或#include <arpa/inet.h>中定义，该结构体解决了sockaddr的缺陷，把port和addr 分开储存在两个变量中，如下：  
  
struct sockaddr_in  
{  
	sa_family_t     sin_family; //地址族  
	uint16_t        sin_port;   //16位tcp/udp端口号  
	struct in_addr  sin_addr;   //32位ip地址  
	char            sin_zero[8] //不使用  
}  
  
struct in_addr  
{  
	in_addr_t	s_addr;   
}  
  
sin_port和sin_addr都必须是网络字节序（NBO），一般可视化的数字都是主机字节序（HBO）。  
  
三、总结  
  
二者长度一样，都是16个字节，即占用的内存大小是一致的，因此可以互相转化。二者是并列结构，指向sockaddr_in结构的指针也可以指向sockaddr。  
  
sockaddr常用于bind、connect、recvfrom、sendto等函数的参数，指明地址信息，是一种通用的套接字地址。   
sockaddr_in 是internet环境下套接字的地址形式。所以在网络编程中我们会对sockaddr_in结构体进行操作，  
使用sockaddr_in来建立所需的信息，最后使用类型转化就可以了。一般先把sockaddr_in变量赋值后，强制类型  
转换后传入用sockaddr做参数的函数：sockaddr_in用于socket定义和赋值；sockaddr用于函数参数。  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
  
int main(int argc,char **argv)  
{  
	int sockfd;  
	struct sockaddr_in mysock;  
  
	sockfd = socket(AF_INET,SOCK_STREAM,0);  //获得fd  
  
	bzero(&mysock,sizeof(mysock));  //初始化结构体  
	mysock.sin_family = AF_INET;  //设置地址家族  
	mysock.sin_port = htons(800);  //设置端口  
	mysock.sin_addr.s_addr = inet_addr("192.168.1.0");  //设置地址  
	bind(sockfd,(struct sockaddr *)&mysock,sizeof(struct sockaddr); /* bind的时候进行转化 */  
	... ...  
	return 0;  
}  
  
题外话，两个函数 htons() 和 inet_addr()。  
  
#将主机字节序的端口号转化为网络字节序的端口号，输入和输出均为数据类型  
htons()   host to net short 16bit  
htonl()   host to net long  32bit  
  
ntohs()   net to host short   
ntohl()   net to host long  
  
  
#将字符串类型的ip地址转化成网络字节序数据类型的数据用于网络连接  
inet_addr()      
  
#将数据类型的ip地址转化为字符串类型的数据  
inet_ntoa()   ip net net to ascii  
  
#将字符串类型的ip地址转化成网络字节序数据类型的数据用于网络连接  
inet_aton()   ip net ascii to net  
  
htons()作用是将端口号由主机字节序转换为网络字节序的整数值。(host to net)  
inet_addr()作用是将一个IP字符串转化为一个网络字节序的整数值，用于sockaddr_in.sin_addr.s_addr。  
inet_ntoa()作用是将一个sin_addr结构体输出成IP字符串(network to ascii)。比如：  
printf("%s",inet_ntoa(mysock.sin_addr));  
  
htonl()作用和htons()一样，不过它针对的是32位的（long），而htons()针对的是两个字节，16位的（short）。  
与htonl()和htons()作用相反的两个函数是：ntohl()和ntohs()。  
  
三种给socket赋值地址的方法：  
sockaddr_in myaddr;  
char ip_string[]="192.168.1.10";  
  
(1)inet_aton(ip_string, &myaddr.sin_addr);  
(2)myaddr.sin_addr.s_addr = inet_addr(ip_string);  
  
(3)myaddr.sin_addr.s_addr = htons(INADDR_ANY);  
   myaddr.sin_addr.s_addr = INADDR_ANY;  
  
两种赋值端口号的方法  
#define   myport  3490  
（1）myaddr.sin_port = htons(myport);  
（2）myaddr.sin_port = 0;  
