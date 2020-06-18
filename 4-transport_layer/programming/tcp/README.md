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
设置Server地址和端口，使用connet函数连接，TCP组包，然后TCP/IP协议栈匹配本地路  
由表，找到对应的发送接口，然后组IP包.......  
  
  
  
TCP Server:  
.....  
