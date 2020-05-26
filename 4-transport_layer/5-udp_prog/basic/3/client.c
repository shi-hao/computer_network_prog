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
#define   BUFF_LEN 65507
//#define SERVER_IP "192.168.0.129"
#define SERVER_IP "39.105.113.152"
//#define SERVER_IP "127.0.0.1"

/*
 * udp client:向指定的ip和port发送udp包，然后睡眠一段时间，继续发送数据包。
 *
 * 传输层(UDP)发送数据长度超过以太网MTU时，三层二层是如何处理的呢？抓包查看协议栈的分包机制。
 * UDP组包发包机制：
 * <发送方>
 * (1)用户通过调用UDP接口将需要发送的数据传入TCP/IP协议栈
 *    进行组包，首先传输层组包加UDP头，UDP包中有包长字段2字节，所以最大的payload长度是65535-8=65527字节，  
 *    如果用户一次发送的数据超过此长度，发送会失败。
 *
 * (2)完整UDP包传入网络层，增加IP头，因为IP包长最大也是2字节，所以当传输层给的数据是65535时，
 *    IP包就溢出了，所以实际上UDP最大的payload是65535-8-20=65507，减去UDP头和IP头。
 *    IP层有分片机制，当IP包的总长度(包头+payload)大于1500字节时，IP包会将划分为多个IP包发送到数据链路层。
 *    这是因为数据两路层以太网帧的最大paylaod是1500字节，IP层为了适应以太网帧所做的策略。
 *
 * (3)IP数据包传入数据链路层，IP包的长度一定是小于等于1500字节的，然后增加以太网头和校验码，发送出去。
 *
 * <接收方>
 * (1)数据链路层根据目的MAC地址接收以太网帧，接收目的MAC是自己的数据包并校验，将校验通过的数据包
 *    payload转发到网络层。
 *
 * (2)网络层收到数据后，校验，然后判断这些包是否是分片数据包，如果不是，直接将payload转发到传输层，  
 *    如果是分片数据包，那么网络层会将接收到分片数据重组为一个完整数据包，将组合后的payload发到传输层。  
 *
 * (3)传输层收到数据包后，校验，然后将payload存入TCP/IP协议栈的缓存中，等待用户调用接口读出发送方发送的
 *    数据。接收方从TCP/IP协议栈缓存中读出数据和发送方是一致的，即发送方调用两次接口发送a和b数据包，那么  
 *    接收方也是触发两次接收，读出a和b数据包，a和b不会交叉在一起。
 *  
 */
void udp_msg_sender(int fd, struct sockaddr* dst)
{
	socklen_t len;
	struct sockaddr_in src;
	int count=0, ret;
	while(1)
	{
		char buf[BUFF_LEN];
		memset(buf, 0x65, BUFF_LEN);

		len = sizeof(*dst);
		printf("client sending:%s\n",buf);  //打印自己发送的信息
		ret = sendto(fd, buf, BUFF_LEN, 0, dst, len);
		printf("ret = %d\n", ret);

#if 0
		memset(buf, 0, BUFF_LEN);
		recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
		printf("server[%s:%d]:%s\n",inet_ntoa(src.sin_addr), ntohs(src.sin_port), buf);
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

	if(argc < 3){
		printf("\n usage : ip port \n");
		exit(0);
	}

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}

#if 0
	struct sockaddr_in local_addr;
	int ret;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(local_IP);
	local_addr.sin_port = 0;  //注意网络序转换

	ret = bind(fd, (struct sockaddr*)&local_addr, sizeof(local_addr));
	if(ret < 0) printf("bind error\n");
#endif

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
