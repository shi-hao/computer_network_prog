<pre>
osi七层模型

1.网络层次
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



传输层：TCP/UDP
  |
网络层：IP
  |
数据链路层：Ethernet Protocol
  |
物理层：MAC


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
|2 bytes           | 2bytes                 |
--------------------------------------------
|optional data                              |
| 0-40bytes                                 |
--------------------------------------------

UDP Header
--------------------------------------------
|source port number |destination port number|
|2 bytes            |2 bytes                |
---------------------------------------------
|length             |checksum               |
|2 bytes            |2 bytes                |
---------------------------------------------

IP Header
---------------------------------------------
|ver  |H len|pri&ser|total len              |
|4bits|4bits|8bits  |2 bytes                |
---------------------------------------------
|identification     |flags|fragmented offset|
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

Ethernet Header
------------------------------------------------------------------------------
|preamble | SFD | des MAC addr | src MAC addr| EtherType |   payload  | FCS  |
|7 bytes  |1byte| 6bytes       |6 bytes      |2 bytes    |46-1500bytes|4bytes|
------------------------------------------------------------------------------





实验：
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
