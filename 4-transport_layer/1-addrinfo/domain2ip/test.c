#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <netdb.h>

#include<unistd.h>


int main(int argc, char **argv)
{

	int status;
	struct addrinfo hints, *res, *this;
	char ipaddr[INET6_ADDRSTRLEN];

#if 1
	//根据域名地址，获取服务器ip
	if(argc == 2) {
		fprintf(stderr, "usage: ./run domain\n");

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;     /* AF_INET(IPv4) AF_INET6(IPv6) */
		hints.ai_socktype = SOCK_STREAM; /* TCP stream sockets */

		if ((status = getaddrinfo(argv[1], NULL, &hints, &res))) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
			return 2;
		}

		printf("IP addresses for %s:\n\n", argv[1]);

	}else if(argc == 1){

		//获取任意地址和回环地址
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;     /* 返回IPv4以及IPV6，也可以指定 AF_INET 或 AF_INET6 */
		hints.ai_socktype = SOCK_STREAM; /* 使用TCP协议 */
		hints.ai_flags = AI_PASSIVE;     /* 返回结果中会填写本地的IP地址 */

		if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
			fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
			exit(1);
		}
	}

#elif 0
	//获取本地所有ip   --貌似不支持这样的操作
	int iRet = 0;
	char szHostName[128] = {0};
	char szHostName2[128] = "localhost";
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;     /* 返回IPv4以及IPV6，也可以指定 AF_INET 或 AF_INET6 */
	hints.ai_socktype = SOCK_STREAM; /* 使用TCP协议 */
	//hints.ai_flags = AI_PASSIVE;     /* 返回结果中会填写本地的IP地址 */

	iRet = gethostname(szHostName, sizeof(szHostName));
	if (iRet != 0)
	{
		fprintf(stderr, "gethostname error!\n");
		exit(1);
	}
	printf("hostname [%s]\n", szHostName);

	if ((status = getaddrinfo(szHostName, NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
#endif

	for(this = res; this != NULL; this = this->ai_next) {
		void *addr;
		char *ipver;

		if (this->ai_family == AF_INET) { /* IPv4 */
			struct sockaddr_in *ipv4;

			ipv4 = (struct sockaddr_in *)this->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { /* IPv6 */
			struct sockaddr_in6 *ipv6;

			ipv6 = (struct sockaddr_in6 *)this->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		/* convert the IP to a string and print it */
		inet_ntop(this->ai_family, addr, ipaddr, sizeof(ipaddr));
		printf("%s:\t%s\n", ipver, ipaddr);
	}

	return 0;
}
