# veth  
一种虚拟的网卡设备，成对出现，一端连接系统tcp/ip协议栈，另一端互相连接。  
即，一个veth接收到来在协议栈的数据，会发送到另一个veth设备上。  
  
  
-------------------------------  
       tcp/ip stack  
--------------------------------  
  |                   |  
  |                   |  
------             ----------  
|veth0|<---------->|veth1|  
-------            ---------  
  
  
  
（1）添加veth网卡设备  
  
#添加网卡设备  
sudo ip link add veth0 type veth peer name veth1  
  
#设置ip地址  
sudo ip addr add 192.168.2.11/24   dev veth0   
  
#启动网卡  
sudo ip link set veth0 up  
sudo ip link set veth1 up  
  
实验  
ping 192.168.2.1  
  
ping不通的，使用tcpdump抓包veth0 veth1会发现，两个网卡都收到了arp请求包，但是没有回应包。  
  
原因：ping使用的是icmp协议，因为本地没有192.168.2.1的mac地址，所以协议栈会发送arp包来请求对应的mac地址，产生arp包通过veth0发送出去，而veth0连接着veth1，所以veth1也接收到了arp请求包，veth1将arp请求包发给协议  
栈，因为本地没有这个网卡，所以arp包被丢弃。  
  
#给veth1配置ip地址  
sudo ip addr add 192.168.2.1/24 dev veth1  
  
  
  
