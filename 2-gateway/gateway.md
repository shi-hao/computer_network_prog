# gateway    
翻译为中文是入口，途径的意思，在网络设备中，被称之为网关。  
网关的的作用其实就是入口的作用，即进入某个网段的入口。  
  
  
使用route -n查看本地的路由表，如下。  
  
Kernel IP routing table  
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface  
0.0.0.0         192.168.0.1     0.0.0.0         UG    100    0        0 eno1  
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 eno1  
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0  
192.168.0.0     0.0.0.0         255.255.255.0   U     100    0        0 eno1  
  
路由设置的有几个重要要素：  
  
[目的网段]：[掩码]：[网关]：[接口]  
 -net       netmask  gw     dev
接口指的是本地的网卡，目的网段是跨网网段，网关的地址要和本地接口在同一网段内。  
route add -net 192.168.1.0 netmask 255.255.255.0 gw 192.168.2.1 dev eno1  
  
（1）一般来说，如果目的网段和本地网卡在一个网段，那么数据包直接从本地网卡路由出去。  
所以，目的地址：掩码：接口 是必须的三项。  
  
（2）如果目的网段和本地网卡不在一个网段，那么必须要设置路由，也就是说，要设置此网段的入口，  
数据包才能被正常路由。  
  
  
<抓包实验>  
以三台机器为例：  
A：ip-192.168.1.10 mac-aa:aa:aa:aa:aa:aa  
B: ip-192.168.1.11 mac-bb:bb:bb:bb:bb:bb  
  
C: ip-192.168.1.1  mac-cc:cc:cc:cc:cc:cc   gateway  
   ip-192.168.2.1  mac-dd:dd:dd:dd:dd:dd   gateway  
  
D: ip-192.168.2.11 mac-dd:dd:dd:dd:dd:dd  
  
A ping B  
S: 192.168.1.10 aa:aa:aa:aa:aa:aa  D: 192.168.1.11 bb:bb:bb:bb:bb:bb  
  
A ping D  
S: 192.168.1.10 aa:aa:aa:aa:aa:aa  D:192.168.2.11 cc:cc:cc:cc:cc:cc  
A ping D，AD不在一个网段，A是不会有D的mac地址的，A会将mac地址填写为网关的mac地址，  
将数据发送给网关。  
