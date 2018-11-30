int getaddrinfo(const char *node, const char *service,
		const struct addrinfo *hints,
		struct addrinfo **res);

struct addrinfo {
	int              ai_flags;
	int              ai_family;
	int              ai_socktype;
	int              ai_protocol;
	socklen_t        ai_addrlen;
	struct sockaddr *ai_addr;
	char            *ai_canonname;
	struct addrinfo *ai_next;
};


getaddrinfo的经典应用：
(1)获取任意地址(0.0.0.0)和回环地址(127.0.0.1)
node         设置为NULL
service      设置为端口号
hints结构体：
 ai_family
　　指定返回地址的协议簇，取值范围:AF_INET(IPv4)、AF_INET6(IPv6)、AF_UNSPEC(IPv4 and IPv6)
 ai_socktype
　　具体类型请查看struct addrinfo 中的 enum __socket_type 类型，用于设定返回地址的socket类型，
　　常用的有SOCK_STREAM、SOCK_DGRAM、SOCK_RAW, 设置为0表示所有类型都可以。
 ai_flags
	此域可以设置多个标志，此处只分析AI_PASSIVE。

    AI_PASSIVE

如果设置了AI_PASSIVE 标志,那么返回的socket地址可以用于bind()函数，
返回的地址是通配符地址(wildcard address, IPv4时是INADDR_ANY，即0.0.0.0， IPv6时是IN6ADDR_ANY_INIT)，
这样应用程序(典型是server)就可以使用这个通配符地址用来接收任何请求主机地址的连接。

如果未设置了AI_PASSIVE 标志,那么网络地址会被设置为lookback接口地址
(IPv4时是INADDR_LOOPBACK 即127.0.0.1,IPv6时是IN6ADDR_LOOPBACK_INIT)，这种情况下，应用是想与运行在同一个主机上
另一个应用通信。
(2)获取本地所有的ip地址
貌似这个函数不支持这样的操作。


(3)根据域名获取远程主机的ip地址
根据域名获取ip地址，很经典的操作。
