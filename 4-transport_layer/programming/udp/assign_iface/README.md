# 绑定TCP Socket到指定物理接口(数据链路层)

当主机拥有多个网卡接口时，可以将Socket绑定到指定的接口，将IP数据包从指定的接口
发送出去。

## setsockopt
使用setsockopt函数，SO_BINDTODEVICE参数，将socket绑定到指定接口。     


可以使用setsockopt函数来绑定指定的网卡发送数据，但是不能和系统的路由表冲突。        
在ubuntu系统下测试发现，如果发送IP数据包指定的接口和路由表发生冲突，IP包也不能正常发出。        
      
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
