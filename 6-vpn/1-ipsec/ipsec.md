# IPSec VPN    
    
## What is IPSec VPN   
    
## IPSec Packet    
<pre>
IKE Packet
</pre>
    
<pre>
IPSec AH Packet
IPSec ESP Packet
</pre>

## Sequence    
(1)Internet Key Exchange(IKE)    
	IKE Phase1 using UDP destination port 500  
	IKE Phase2 using UDP destination port 500  
(2)IPSec ESP Protocol     
	IPSec ESP Protocol using IP type 50  
	  
    
## Compatiblility with NAT  
AH Protocol  
IPSec AH协议使用IP类型51，将IP头的源/目的地址纳入了校验范围，而NAT会改变IP头源和目的地址，  
数据到对端后，AH校验会失败，所以AH协议不兼容NAT。    
  
ESP Protocol  
IPSec ESP协议使用IP类型50，没有将IP头的源/目的地址纳入校验范围，所以可以兼容  
NAT，虽然能够兼容NAT，但是因为ESP协议中并没有类似TCP/UDP端口号字段，所以NAT  
在端口映射时只能映射IP地址，所以NAT后端网络只能一台设备能和VPN server正常通信，  
而且NAT网关可能会直接丢弃该数据包。    
    
ESP兼容NAT方法  
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
IPSec IKE阶段使用UDP协议，ESP对下使用IP协议，对NAT兼容性不好，可能NAT设备    
直接丢弃，可能转发后无法回包。    
SSL VPN对下使用TCP，完美兼容NAT。    
    
## StrongSwan
(1)安装strongswan及其charon插件
apt-get install strongswan
apt-get install libcharon-extra-plugins

(2)重启strongswan服务器
systemctl restart strongswan

(3)添加ipsec服务到开启启动
systemctl enable strongswan

(4)启动IPSec连接
sudo ipsec up <connection>

(5)查看strongswan日志信息
strongswan日志在/var/log/syslog文件中

## StrongSwan Application    
### site to site, server and client all behind NAT
  
### site to site, client behind NAT?    
  
### site to site, server and client all using public IP address?  
