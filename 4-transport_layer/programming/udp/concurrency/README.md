linux socket tcp-udp  
  
1.有无连接  
tcp是面向连接的，udp则是无连接  
tcp有握手机制（发送数据之前，握手建立连接），确认机制（数据包有应答），重传机制（无应答视作丢失，则重传）。  
udp则没有以上机制。  
可以通过wireshark抓包来分析以上特性。  
  
tcp只能是一对一，就是说，一个tcp服务进程(线程)只能响应一个tcp客户端进程(线程)，  
tcp复合服务器一般是通过多进程(线程)来实现的，即启动多个进程（线程）相应客户端请求。  
udp可以一对一，一对多。  
  
2.编程流程  
tcp编程流程  
server:  
创建socket --> 绑定ip和端口号到socket -->设置对大连接数listen -->  接收连接accept --> read/write  recv/send recvfrom/sendto  
  
client:  
创建socket --> 连接服务器connect --> read/write recv/send recvfrom/sendto  
  
tcp的服务端和客户端编程流程固定，必须是如上格式。  
客户端连接上服务端后，双方可以根据自身需要选择收或者发数据。  
  
udp编程流程  
server:  
socket --> bind --> recvfrom/sendto  
  
client:  
client -->sendto/recvfrom  
  
  
(1)一般而言，服务端先recvfrom数据，然后根据受到的数据和ip地址信息回复对端。  
客户端一般先sendto数据到服务端，然后recvfrom数据。  
  
客户端也可以bind地址。bind之后，使用recvfrom接收数据，接收的是以绑定地址为目标的数据。  
如果不bind，先进行sendto，然后recvfrom也可以接收数据，此时目标地址是系统给分配的。  
  
(2) read recv  recvfrom 区别  
ssize_t read(int fd, void *buf, size_t count);  
ssize_t recv(int sockfd, void *buf, size_t len, int flags);  
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,  
                 struct sockaddr *src_addr, socklen_t *addrlen);  
  
ssize_t write(int fd, const void *buf, size_t count);  
ssize_t send(int sockfd, const void *buf, size_t len, int flags);  
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,  
               const struct sockaddr *dest_addr, socklen_t addrlen);  
