# 网络协议 
 
## osi七层模型 
以太网通信体系中，通信协议是分层次架构的，各个层次协议之间是嵌套关系，组包是层 
层嵌套，拆包是层层剥离，实现不同层次协议之间协同工作。 
以太网通信体系中，通信协议是分层次架构的，各个层次协议之间是嵌套关系，时代是是
是
<pre> 
网络层次 
简单理解，五层： 
应用层 
  | 
传输层 
  | 
网络层 
  | 
数据链路层 
  | 
物理层 
 
 
应用层通过socket接口将输入传入协议栈。 
协议栈根据目的ip地址，根据本地的路由表选择从哪个网口路由出去。 
(1)如果路由带网关，那么再添加以太网帧头时，目的mac地址就填写为网关的mac地址。 
(2)如果路由没有网关，那么协议栈要根据本地的mac地址表（arp表），填写目标ip的mac地址， 
如果本地的mac地址表没有指定ip的mac地址，那么主机需要向网络中发送arp广播请求包来请求mac地址。 
</pre> 
 
 
## 经典常用协议 
<pre> 
传输层：TCP/UDP 
  | 
网络层：IP 
  | 
数据链路层：Ethernet Protocol 
  | 
物理层： 
</pre> 
 
### Ethernet Protocol 
以太网协议   
 
<pre> 
Ethernet Header 
------------------------------------------------------------------------------ 
|preamble | SFD | des MAC addr | src MAC addr| EtherType |   payload  | FCS  | 
|7 bytes  |1byte| 6bytes       | 6 bytes     | 2 bytes   |46-1500bytes|4bytes| 
------------------------------------------------------------------------------ 
</pre> 
SFD : start of frame delimiter   
FCS : frame checke sequence(32-bit CRC)   
以太网报文使用CRC校验算法。   
 
 
问：以太网协议报文中并没有frame长度的信息，那如何去判断一个frame的长度呢？   
答：frame中虽然没有长度信息，但是物理层有标识长度的机制，以太网依赖于物理层去区分   
两个frame数据包。   
 
问：以太网报文的最大长度？   
答：以太网报文最大长度不会超过1500bytes，这是报文格式规定的最大长度，即，MTU为1500bytes。     
 
### internet protocol 
网络协议，分IPv4和IPv6。   
 
<pre> 
IPv4 Header 
--------------------------------------------- 
|ver  |IHL |DSCP|ECN|total length           | 
|4b   |4b  |6b  |2b |2 bytes                | 
--------------------------------------------- 
|identification     |flags|fragmen offset   | 
|2 bytes            |3bits|13bits           | 
-------------------------------------------- 
|ttl     |protocol  |Header checksum        | 
|8 bits  |8 bits    |2 bytes                | 
--------------------------------------------- 
|source IP address                          | 
|4 bytes                                    | 
--------------------------------------------- 
|destination IP address                     | 
|4 bytes                                    | 
--------------------------------------------- 
|options (up to 32 bits)                    | 
--------------------------------------------- 
</pre> 
 
version:for IPv4, this is always equal to 4.   
IHL:internet header length   
DSCP:Differentiated Services Code Point    
ECN:Explicit Congestion Notification   
ttl:time to live   
 
IP header中既包含了ip头长度的字段，也包含了整个ip包长度的字段，MTU为65535bytes。   
 
 
 
### TCP & UDP 
 
<pre> 
TCP Header 
-------------------------------------------- 
|source port number |destination port number| 
|2 bytes            |2 bytes                | 
--------------------------------------------- 
|sequence number                            | 
|4 bytes                                    | 
-------------------------------------------- 
|acknowlegement number                      | 
|4 bytes                                    | 
-------------------------------------------- 
|offset|  rev|flags|window size             | 
|4bits |3bits|9bits|2bytes                  | 
--------------------------------------------- 
|checksum          | urgent pointer         | 
|2 bytes           | 2 bytes                | 
-------------------------------------------- 
|optional data                              | 
| 0-40bytes                                 | 
-------------------------------------------- 
</pre> 
 
 
offset:data offset，用来标识TCP头的长度。   
 
 
<pre> 
UDP Header 
-------------------------------------------- 
|source port number |destination port number| 
|2 bytes            |2 bytes                | 
--------------------------------------------- 
|length             |checksum               | 
|2 bytes            |2 bytes                | 
--------------------------------------------- 
</pre> 
 
length:整体的报文长度，包含头和数据部分，MTU为65535。    
 
 
## MTU(maximum transmission unit) 
<pre> 
------------------------------------------------- 
|protocol       |  MTU(byte)                 | 
------------------------------------------------- 
|ethernet       |  1500                      | 
------------------------------------------------- 
|ip             |  65535                     | 
------------------------------------------------- 
|TCP            |  65535                     | 
------------------------------------------------- 
|UDP            |  65535                     | 
------------------------------------------------- 
</pre> 
以上协议中，只有TCP在报文中没有包长度字段，但是window size的最大值是65535，所以   
最大包的长度也是65535。   
因为数据链路层的以太网协议最大的MTU只有1500，所以，包长的瓶颈在数据链路层，如果   
上层的数据包长度大于1500，那么在数据链路层会发生数据拆包。所以一般而言，TCP/IP的   
最大包长都设置为1500。   
 
 
 
## 实验 
<pre> 
----------------- 
 |   switch    | 
----------------- 
 |             | 
 |             | 
----          ---- 
pc 1|         |pc2| 
----          ---- 
192.168.0.1   192.168.0.2 
 
pc1端增加如下路由 
#目标网段+掩码+网关+接口 
route -net 192.168.4.0 netmask 255.255.255.0 gw 192.168.0.2 dev eth0 
 
在pc1上使用ping命令ping 192.168.4.1，使用wireshark在pc2上抓包，可以抓到icmp包，查看包的mac地址， 
可以清楚的看到，包的目的mac地址是pc2的mac地址，数据包转发到了pc2。 
 
pc1端删除以上路由，重新添加如下路由 
#目标网段 + 掩码 + 接口，未指定网关地址 
route -net 192.168.4.0 netmask 255.255.255.0  dev eth0 
 
在pc1上使用ping命令ping 192.168.4.1，使用wireshark在pc2上抓包，可以抓到arp请求包，请求192.168.4.1的mac 
地址，因为arp请求是广播的，所以pc2收到了pc1的arp请求包。 
</pre> 
