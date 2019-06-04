# basic tcp prog steps:
server:
  （1）创建socket
  （2）创建地址结构sockaddr_in,并初始化结构，初始化的地址是本地网卡的地址
  （3）绑定socket和sockaddr_in，bind，bind的作用是让socket在指定的
       的ip和端口收发数据。
  （4）listen，设置最大连接数目
  （5）accept，等待客户端连接。


client:
  （1）创建socket
  （2）创建地址结构sockaddr_in,并初始化结构，初始化的地址是远端服务器的地址和端口
  （3）connect，使用socket和sockaddr_in连接远端服务器。


