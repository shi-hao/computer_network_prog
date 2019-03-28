# TCP/UDP client bind to specific interface    
  
可以使用setsockopt函数来绑定制定的网卡发送数据，但是要和    
系统的路由表不冲突。    
  
在ubuntu系统下测试发现，如果指定的接口和路由表发生冲突，    
IP包也不能正常发出。    
  
举例：  
  
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface  
0.0.0.0         192.168.131.2   0.0.0.0         UG    100    0        0 ens33  
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 ens33  
192.168.131.0   0.0.0.0         255.255.255.0   U     100    0        0 ens33  
192.168.130.0   0.0.0.0         255.255.255.0   U     100    0        0 ens44  
  
  
如果TCP/UDP的server地址是192.168.10.10，如果绑定接口ens44发送数据包，其实IP包无法正常    
发出，因为和路由表冲突。  
