# IPSec VPN  
  
## What is IPSec  
  
## IPSec Packet  
  
## Sequence  
(1)Internet Key Exchange(IKE) using UDP destination port 500  
(2)IPSec AH/ESP Protocol communication using IP type 51/50  
  
**IPSec是否兼容NAT**  
(1)IPSec的AH协议不兼容NAT，因为AH协议中对IP头的源/目的地址纳入了校验范围，因为  
NAT会改变IP头的源和目的地址，数据到对端后，验证会失败，所以不兼容。  
(2)IPSec的ESP协议兼容NAT，协议本身对IP头没有进行校验。  
(3)IPSec ESP协议的IP协议类型是50，虽然能够兼容NAT，但是因为ESP协议中并没有类似  
TCP的端口号字段，所以NAT无法映射，有可能直接丢弃。  
  
UDP Encapsulation of ESP  
Because ESP packets are unidirectional, NAT devices can't map them like they  
do with e.g. TCP/UDP packets by using the source and destination ports in  
those headers. Some NAT devices have a feature, often called something like  
"IPsec passthrough", that detects IKE traffic from a single host behind the  
NAT and will forward incoming plain ESP packets to that host. But that won't  
work with multiple clients behind the same NAT that use the same server. To  
allow multiple clients UDP encapsulation is used. Adding a UDP header to the  
ESP packets allows NAT devices to treat them like the IKE packets (or any  
other UDP packets) and to maintain port mappings to forward the packets from/to  
the correct hosts behind the NAT.  
  
## Difference between IPSec VPN and SSL VPN  
(1)应用模式  
IPSec VPN典型应用模式是网关到网关（site to site），为网域内的其他主机设备提供安全  
通道来访问对端网域内的主机设备。  
SSL VPN典型应用模式是主机设备到网关，为主机设备上的其他应用程序提供安全通道访  
问网关网域内的主机设备。  
  
(2)技术实现  
IPSec IKE阶段使用UDP协议，ESP对下使用IP协议，所以对NAT兼容性不好，可能NAT设备  
直接丢弃，可能转发后无法回包。  
SSL VPN对下使用TCP，完美兼容NAT。  
  
## Application  
IPSec site to site with client behind NAT?  
  
