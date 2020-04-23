# Data Link Layer  
数据链路层的核心协议是以太网协议，协议的核心字段是MAC地址。    
  
**MAC**  
**单播/组播/广播**  
**MAC地址表/ARP表**  
  
# MAC(media access control address)      
mac地址，又称为物理地址(pyhsical address)，长度固定，6个字节，mac地址也分为三种，单播，组播，    
广播地址。        
      
## 单播(unicast)      
单播地址，就是对应网卡的实际物理地址，根据ip包的目的ip地址，查询arp表获取，或者是网关的      
mac地址。网卡的物理地址的第一个字节的最低位必须是0！！        
      
## 组播(multicast)      
组播mac地址的第一个字节的最低位必须是1，比如如下都是组播地址。        
0x01-0xff-0xff-0xff-0xff-0xff        
0x33-0x00-0x00-0x00-0x00-0x00        
      
## 广播(broadcast)      
广播的mac地址很固定，是全1，即：        
0xff-0xff-0xff-0xff-0xff-0xff        
    
# 交换机基本原理    
数据链路层的核心设备是交换机，交换机运作的核心数据是MAC地址和接口对应表(MAC表)。    
交换机正常工作后，会在本地建立一个接口地址表，表内存储接口号和连接此接口  
主机的MAC地址，比如：    
<pre>  
MAC地址								接口      
0xdd-0xee-0xcc-0x11-0xff-0xff		inter0  
0xee-0xee-0xcc-0x11-0xff-0xff       inter0  
0xcc-0xee-0xcc-0x11-0xff-0xff		inter0              
  
0xaa-0xee-0xcc-0x11-0xff-0xff		inter1  
</pre>  
交换机正常运行后，会记录接口收到的以太网数据包的源MAC地址，将MAC地址填入MAC表。  
然后查询MAC地址表中是否有以太网数据包的目的MAC地址，如果有，则从对应接口转发  
数据包，如果没有，那将数据发向除接收口之外的所有接口。  
交换机的一个接口可以对应多个MAC地址，比如交换机互相连接，那么连接的接口就可能对应多个MAC地址。    
  
  
ARP协议的本质是根据通过目的IP地址请求目的MAC地址，通过发送以太网广播数据包来  
请求MAC地址，将收到的MAC填入ARP缓存表，ARP缓存表存储的是IP地址和MAC地址的对应关系。  
<pre>  
IP					MAC									   
192.168.1.99		0xdd-0xee-0xcc-0x11-0xff-0xff		  
192.168.1.100		0xee-0xee-0xcc-0x11-0xff-0xff         
192.168.1.80		0xcc-0xee-0xcc-0x11-0xff-0xff		             
  
192.168.2.100		0xaa-0xee-0xcc-0x11-0xff-0xff		  
</pre>  
  
**MAC地址表/ARP表更新和老化**   
MAC地址表是二层数据转发的依据，

