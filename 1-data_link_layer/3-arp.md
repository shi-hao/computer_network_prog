#arp--Address Resolution Protocol      
      
## What is ARP?  
The Address Resolution Protocol (ARP) is a communication protocol used for discovering the link   
layer address, such as a MAC address, associated with a given internet layer address, typically   
an IPv4 address. This mapping is a critical function in the Internet protocol suite. ARP was   
defined in 1982 by RFC 827,[1] which is Internet Standard STD 37.       
      
The Address Resolution Protocol is a request-response protocol whose messages are encapsulated   
by a link layer protocol. It is communicated within the boundaries of a single network, never   
routed across internetworking nodes. This property places ARP into the link layer of the   
Internet protocol suite.[2]      
      
Two computers in an office (Computer 1 and Computer 2) are connected to each other in a local   
area network by Ethernet cables and network switches, with no intervening gateways or routers.  
Computer 1 has a packet to send to Computer 2. Through DNS, it determines that Computer 2 has  
the IP address 192.168.0.55. To send the message, it also requires Computer 2's MAC address.   
First, Computer 1 uses a cached ARP table to look up 192.168.0.55 for any existing records of  
Computer 2's MAC address (00:eb:24:b2:05:ac). If the MAC address is found, it sends an Ethernet  
frame with destination address 00:eb:24:b2:05:ac, containing the IP packet onto the link. If  
the cache did not produce a result for 192.168.0.55, Computer 1 has to send a broadcast ARP   
message (destination FF:FF:FF:FF:FF:FF MAC address), which is accepted by all computers on the  
local network, requesting an answer for 192.168.0.55. Computer 2 responds with its MAC and IP  
addresses.  Computer 2 may insert an entry for Computer 1 into its ARP table for future use.      
Computer 1 caches the response information in its ARP table and can now send the packet.[7]       
      
## ARP基本原理  
**arp报文格式**      
<pre>    
---------------------------    
| 14 byte Ethernet Header|     
---------------------------    
| 28 byte arp packet     |    
--------------------------    
| 4 byte Ethernet CRC    |    
--------------------------    
    
--------------------------------------------    
| 6 byte destination mac                   |    
--------------------------------------------    
| 6 byte source mac                        |    
--------------------------------------------    
|frame  type |hardware type|protocol type  |    
|2 byte      |2 byte       |2 byte         |    
--------------------------------------------    
|len1  |len2 |op code      |    
|1b    |1b   |2 byte       |    
--------------------------------------------    
| 6 byte source mac                        |    
--------------------------------------------    
| 6 byte source protocol address           |    
--------------------------------------------    
| 6 byte destination mac                   |    
--------------------------------------------    
| 6 byte destination protocol address      |    
--------------------------------------------    
    
len1 : hardware address length    
len2 : protocol address length    
    
op code : operation code,     
 1 arp request     
 2 arp ack    
 3 rarp request    
 4 rarp ack    
    
硬件类型：如以太网（0x0001）、分组无线网。    
协议类型：如网际协议(IP)（0x0800）、IPv6（0x86DD）。    
硬件地址长度：每种硬件地址的字节长度，一般为6（以太网）。    
协议地址长度：每种协议地址的字节长度，一般为4（IPv4）。    
操作码：1为ARP请求，2为ARP应答，3为RARP请求，4为RARP应答。    
源硬件地址：n个字节，n由硬件地址长度得到，一般为发送方MAC地址。    
源协议地址：m个字节，m由协议地址长度得到，一般为发送方IP地址。    
目标硬件地址：n个字节，n由硬件地址长度得到，一般为目标MAC地址。    
目标协议地址：m个字节，m由协议地址长度得到，一般为目标IP地址。    
</pre>    
主机A需要和主机B通信，已知B的IP地址为192.168.1.100，首先主机A发送ARP Request，  
ARP报文中源MAC和源IP都填写A的实际地址，目的IP填写目的IP，目的MAC填全0，op code  
填为ARP Request，然后进行以太网组包，源MAC地址填写A的地址，目的地址填写全1，即  
发送以太网广播。  
主机B收到广播后，查看ARP Request包发现对端在请求自己的MAC地址，然后回应一个ARP  
ACK给A，ARP包中源MAC和源IP填写B的地址，目的MAC和目的IP填写A的地址，op code填写  
为ARP ACK，二层组包时源MAC填写B的地址，目的MAC填写A的地址，即单播回应。  
  
## 免费ARP(gratuitous ARP)  
当主机配置了IP地址时，主机会发送免费ARP包来确认网络中是否有设备和自己的IP地址  
冲突，即发送一个ARP Requst，源MAC和源IP地址设定为自己的，目的IP也设置为自己的  
IP地址，目的MAC设置为全0。  
目前，很多网络设备已经不再发送免费ARP报文了，是否发送要看具体设备了。    
  
  
## ARP Table  
原则上ARP表只包含两个内容，IP地址及其对应的MAC地址，不过在一些PC设备上，ARP表  
也包含接口信息。  
  
## ARP欺骗   
ARP欺骗的核心原理很简单，当网络中有设备发送ARP Request时，按照正常流程，对应的  
主机回应ARP ACK，但是有些欺骗者会在网络中发送一些假的ACK数据包，将数据包中MAC  
修改为自己的MAC，其他设备收到该ACK后，会更新自己的ARP表，将MAC修改为错误的MAC  
当主机发送IP数据包时，对应MAC地址被改为了错误的MAC，交换机交换数据时，会被导向  
攻击者。  
ARP欺骗主要利用的ARP协议本身对ARP回应没有做安全机制的漏洞，后回应的ARP ACK会刷  
新本地的ARP表，导致数据在二层交换时，被导向错误的主机(攻击者)。  
