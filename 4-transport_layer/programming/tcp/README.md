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
      
    
## TCP/IP协议栈处理数据基本流程    
TCP Client：    
设置Server IP地址和端口，使用connet函数连接，TCP组包，然后TCP/IP协议栈匹配本地路    
由表，找到对应的发送接口，然后组IP包，根据匹配到的路由，组以太网包，从指定接口  
发送出去。  
    
TCP Server:    
设置监听的IP地址和端口，创建socket并绑定IP地址和端口，然后accept开始监听连接数  
据包，当网卡收到数据包后，首先匹配MAC地址是否和网卡一样，不匹配，则丢弃，匹配  
则收下数据包，进一步查看IP数据包是否和网卡IP地址一样，IP地址不一样，则转发或者  
丢弃，一样则收下，进一步查看TCP端口号，TCP/IP协议栈匹配是否有进程在监听此IP地  
址和端口号，有则将数据TCP包的载荷数据转发给对应的进程。    
