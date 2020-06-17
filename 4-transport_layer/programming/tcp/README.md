# TCP Programming
## Basic TCP Programming Steps:  
server:  
  （1）创建socket  
  （2）创建地址结构sockaddr_in,并初始化结构，初始化的地址是本地网卡的地址  
  （3）使用bind函数，绑定socket和sockaddr_in。  
  （4）listen，设置最大连接数目  
  （5）accept，等待客户端连接。  
  
  
client:  
  （1）创建socket  
  （2）创建地址结构sockaddr_in,并初始化结构，初始化的地址是远端服务器的地址和端口  
  （3）connect，使用socket和sockaddr_in连接远端服务器。  
  
  

## bind函数  
(1)bind函数的作用是，将socket和指定的IP地址和端口号绑定，表示该socket以指定的
IP地址和端口号发送数据，在指定的IP和端口号上接收数据。  
(2)bind函数指定的IP地址必须是主机本地网卡的IP地址，或者是全0，表示本地任意一个
网卡地址。
(3)bind仅仅表示在指定的IP和端口号发送接收数据，具体通过哪个物理接口发送数据，
根据系统的路由表决定，或者使用setsockopt函数设置使用哪个接口发送数据。  
(4)数据包到达网卡后，先匹配目的MAC地址是否匹配，不匹配在丢掉数据包，匹配则查看
目的IP地址是否匹配，不匹配，则丢弃，如果开启了转发，那么查本地路由表进行转发，
如果匹配，那么继续查看端口号，并检测系统是否有进程在该IP和端口号下监听数据，有
则将数据转发给进程。
