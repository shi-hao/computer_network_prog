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


# TCP/UDP client bind to specific interface        
      
可以使用setsockopt函数来绑定指定的网卡发送数据，但是要和        
系统的路由表不冲突。        
      
在ubuntu系统下测试发现，如果指定的接口和路由表发生冲突，        
IP包也不能正常发出。        
      
举例：      
example1    
  
route -n       
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface      
0.0.0.0         192.168.131.2   0.0.0.0         UG    100    0        0 ens33      
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 ens33      
192.168.131.0   0.0.0.0         255.255.255.0   U     100    0        0 ens33      
192.168.130.0   0.0.0.0         255.255.255.0   U     100    0        0 ens44      
      
      
如果TCP/UDP的server地址是192.168.10.10，如果绑定接口ens44发送数据包，其实IP包无法正常        
发出，因为和路由表冲突，目的地址匹配路由表后，应该从默认路由发出。      
    
example2    
    
route -n    
Kernel IP routing table  
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface  
0.0.0.0         192.168.8.1     0.0.0.0         UG    20100  0        0 enx000ec6be0723  
0.0.0.0         192.168.8.1     0.0.0.0         UG    20600  0        0 wlp4s0  
192.168.8.0     0.0.0.0         255.255.255.0   U     100    0        0 enx000ec6be0723  
192.168.8.0     0.0.0.0         255.255.255.0   U     600    0        0 wlp4s0  
  
两个网卡，同时可以上网，指定一个接口发送TCP/UDP数据包。    

