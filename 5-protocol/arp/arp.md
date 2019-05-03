#arp--Address Resolution Protocol  
  
The Address Resolution Protocol (ARP) is a communication protocol used for discovering the link layer
address, such as a MAC address, associated with a given internet layer address, typically an IPv4 address.   
This mapping is a critical function in the Internet protocol suite. ARP was defined in 1982 by RFC 827,  
[1] which is Internet Standard STD 37.   
  
简单来说，arp协议就是发现链路层地址(mac地址)的协议，已知ip地址，在网络上发送请求包，搜寻其mac地址。  
  
The Address Resolution Protocol is a request-response protocol whose messages are encapsulated by a   
link layer protocol. It is communicated within the boundaries of a single network, never routed across  
internetworking nodes. This property places ARP into the link layer of the Internet protocol suite.[2]  
  
arp包只会在一个单独网域内传播，不会在网关之间转发传播。  
  
Two computers in an office (Computer 1 and Computer 2) are connected to each other in a local area network  
by Ethernet cables and network switches, with no intervening gateways or routers. Computer 1 has a packet  
to send to Computer 2. Through DNS, it determines that Computer 2 has the IP address 192.168.0.55.  
To send the message, it also requires Computer 2's MAC address. First, Computer 1 uses a cached ARP table to   
look up 192.168.0.55 for any existing records of Computer 2's MAC address (00:eb:24:b2:05:ac).   
If the MAC address is found, it sends an Ethernet frame with destination address 00:eb:24:b2:05:ac,   
containing the IP packet onto the link. If the cache did not produce a result for 192.168.0.55, Computer 1 
has to send a broadcast ARP message (destination FF:FF:FF:FF:FF:FF MAC address), which is accepted by all computers on the local network, requesting an answer for 192.168.0.55. Computer 2 responds with its MAC and IP addresses.  Computer 2 may insert an entry for Computer 1 into its ARP table for future use.  
Computer 1 caches the response information in its ARP table and can now send the packet.[7]   
  
很好的例子，阐释了arp协议的工作原理。


**arp报文格式**  
<pre>
---------------------------
| 14 byte Ethernet Header| 
---------------------------
| 28 byte arp packet     |
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
arp协议对下使用的ethernet协议，广播，并不使用ip协议！！  

