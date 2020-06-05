# ARP--Address Resolution Protocol              
    
## 1.What is ARP and used for? 
名词解释：ARP，address resolution protocol，地址解析协议。  
用    途：已知目的主机的IP地址，请求目的主机的MAC地址。  
  
## 2.ARP Packet  
<pre>  
ARP对下使用以太网协议，组包如下所示。  
---------------------------            
| 14 byte Ethernet Header |             
---------------------------            
| 28 byte arp packet      |            
---------------------------            
| 18 byte Ethernet padding|            
---------------------------            
| 4 byte Ethernet CRC     |            
---------------------------            
</pre>  
**arp报文格式**              
<pre>            
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
 2 arp ack(arp reply)            
 3 rarp request            
 4 rarp ack            
            
硬件类型：如以太网（0x0001）、分组无线网。            
协议类型：如网际协议(IP)（0x0800）、IPv6（0x86DD）。            
硬件地址长度：每种硬件地址的字节长度，一般为6（以太网）。            
协议地址长度：每种协议地址的字节长度，一般为4（IPv4）。            
操作码：1为ARP请求，2为ARP应答，3为RARP请求，4为RARP应答。            
源硬件地址：n个字节，n由硬件地址长度得到，一般为发送方MAC地址。            
源协议地址：m个字节，m由协议地址长度得到，一般为发送方IP地址？？？6字节？？？。            
目标硬件地址：n个字节，n由硬件地址长度得到，一般为目标MAC地址。            
目标协议地址：m个字节，m由协议地址长度得到，一般为目标IP地址？？？6字节？？？。            
</pre>            
  
## 3.Sequence  
ARP协议对下使用以太网协议，广播请求，单播回应。  
主机A(192.168.1.60)和主机B(192.168.1.100)通信，MAC地址未知。  
<pre>  
A主机发送arp request，关键字段如下填充。  
arp-type      |arp request  
arp-s-ip      |192.168.1.60(主机A的IP)  
arp-s-mac     |aa-bb-cc-dd-ee-ff(主机A的MAC)  
arp-d-ip      |192.168.1.100(主机B的IP)  
arp-d-mac     |00-00-00-00-00-00(目的主机未知，填0)  
  
ethernet-d-mac|ff-ff-ff-ff-ff-ff(广播)  
ethernet-s-mac|aa-bb-cc-dd-ee-ff  
  
B主机接收到广播后，解析ARP包，发现目的IP是自己，会回复arp reply。  
arp-type      |arp reply  
arp-s-ip      |192.168.1.100(主机B的IP)  
arp-s-mac     |gg-bb-cc-dd-ee-ff(主机B的MAC)  
arp-d-ip      |192.168.1.60(主机A的IP)  
arp-d-mac     |aa-bb-cc-dd-ee-ff(主机A的MAC)  
  
ethernet-d-mac|aa-bb-cc-dd-ee-ff(单播)  
ethernet-s-mac|gg-bb-cc-dd-ee-ff  
  
广播请求，单播回应  
</pre>  
  
## ARP Table          
ARP根据收到的ARP包的源IP和MAC地址产生，包含两部部分，IP地址和对应的MAC地址。
ARP是实时更新的，收到ARP包就会刷新，后来覆盖先到，ARP老化时间一般是20分钟。
<pre>
ARP Table
---------------------------------------------------------
| IP Address               | MAC Address               |
---------------------------------------------------------
| 192.168.1.100            | 03-4e-ee-ff-gg-gg         |
| 192.168.1.200            | 03-dd-ff-bb-cc-aa         |
---------------------------------------------------------
</pre>
问：ARP表和MAC地址表的区别？        
答：ARP表包含的是IP和MAC地址的对应关系，根据收到的ARP包的源地址产生并刷新。        
	MAC表包含MAC地址，接口，类型，VLAN ID，根据收到的以太网帧的源地址产生并刷新。      
    
## 免费ARP(gratuitous ARP)          
免费ARP简单来说就是自己请求或者回应自己。        
(1)免费ARP Request        
将ARP报文中的发送MAC和发送IP设置为本地的相应地址，然后目的IP设置为本地IP地址，          
目的MAC设置为全0，以太网层设置为广播，那么这个ARP报文就广播到全网。        
这种情况经常用来检测网络中是否有设备和自己的IP地址有冲突。        
        
(2)免费ARP Reply        
常规的ARP Reply的源MAC和源IP设置为本机的地址，目的MAC和IP设置为对端的MAC和IP，          
但是免费ARP Reply将目的IP也设置为本地IP，目的MAC则设置为全0，以太网层设置为广        
播，ARP报文会广播到全网。        
网络设备是根据收到的ARP Reply来更新本地的ARP表，这种操作在一定程度上可以防止        
网络内的其他主机占用某个IP，比如网关会不停在网络内广播此免费ARP报文，一定程度        
上也可以防御低频率的ARP欺骗攻击。        
        
## ARP欺骗           
ARP欺骗的核心原理很简单，当网络中有设备发送ARP Request时，按照正常流程，对应的          
主机回应ARP Reply，但是有些欺骗者会在网络中发送一些假的Reply数据包，将数据包中MAC          
修改为自己的MAC，其他设备收到该Reply后，会更新自己的ARP表为错误的MAC，          
当主机发送IP数据包时，以太网帧被填充错误的MAC，交换机交换数据时，被导向攻击者。          
ARP欺骗主要利用的ARP协议本身对ARP回应没有做安全机制的漏洞，后回应的ARP Reply会刷          
新本地的ARP表，导致数据在二层交换时，被导向错误的主机(攻击者)。          
    
ARP欺骗主要攻击形式：      
ARP欺骗攻击可以指定某个具体的主机，也可以无差别的进行广播，欺骗整个二层网络的所有      
主机，通常情况下，ARP攻击会伪装网关的MAC地址，攻击局域网内的具体主机或全部主机。    
也可能伪装成主机向网关发送虚假的MAC地址。    
    
ARP欺骗的防御方式：    
1.设置静态MAC地址，主机可以将网关的MAC地址设置为静态地址，不通过ARP协议获取MAC地址。      
    
2.网络行为分析，可以分析网络中ARP Reply包，将高频率发送ARP Reply的主机判定为攻击者。  
然后丢弃该ARP Reply报文。    
    
3.还有一种方式是，加大发送ARP Reply频率，超过攻击者的发送频率，这种方式在网络    
内产生大量的ARP报文，会造成网络瘫痪。    
    
对于ARP攻击目前没有很好的防御手段，所以ARP协议在IPv6协议中已经被废弃了。    
    
## P2P终结者，ARP防火墙    
