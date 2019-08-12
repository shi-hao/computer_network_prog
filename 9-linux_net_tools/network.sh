#!/bin/bash 

#config the interface
#ifconfig [interface]  up/down  打开关闭网卡
#ifconfig [interface] [ip] netmask [mask]  设置网卡ip及其掩码
ifconfig enp0s31f6 down 
ifconfig enp0s31f6 11.15.244.64 netmask 255.255.255.0 
ifconfig enp0s31f6 up

#iwconfig, similar to ifconfig, interface wireless config    
#print wireless card info    
iwconfig  [interface]    
  
#set the wireless card mode key essid channel    
sudo  iwconfig  wlp4s0  mode  ad-hoc    
sudo  iwconfig  wlp4s0  channel  auto    
sudo  iwconfig  wlp4s0  essid  wifi_name     
sudo  iwconfig  wlp4s0  key  1234567890    

#route -n  查看路由表
#route add -host [ip] dev [interface]  增加静态路由，主机
#route add -net [ip] netmask [mask] gw [ip] dev [interface]  增加静态路由，网段
route -n
route add -host 192.168.100.100 dev enp0s31f6 
route add -net  192.168.100.0 netmask 255.255.255.0 gw 192.168.100.1 dev enp0s31f6


#arp -n 查看mac地址表
arp -n


#netstat -an  查看tcp/udp等连接状况 -a all -n number
#netstat -ant 查看tcp
#netstat -anu 查看udp
#netstat -g   查看组播成员关系
netstat  -an 
netstat  -t
netstat  -u


#数据包在网络内路由，如何才能知道数据经过了哪些路由设备呢？这是一个很有意思的事情。  
#traceroute工具是用来做这个事情的，traceroute的基本原理是利用了ip header中的ttl字段，
#通过使用tcp,udp或者icmp协议，设置ip包的ttl值依次从1递增，发送数据包，因为路由在收到
#数据包后，会将ip包的ttl减1，如果ttl为0了，网关不再转发这个包，会将这个包丢弃，同时会给
#发送包的主机回应一个丢弃ip包的回应，traceroute就是利用这个特性来探测路由信息。
#traceroute [ip or domain]
traceroute  www.baidu.com


#
# 使用icmp探测：
# bleach@bleach-ThinkPad-X1-Carbon-5th:~$ sudo traceroute -I -n  www.baidu.com
# [sudo] password for bleach: 
# traceroute to www.baidu.com (61.135.169.121), 30 hops max, 60 byte packets
#  1  192.168.8.1  3.409 ms  3.454 ms  5.454 ms
#  2  192.168.3.1  9.082 ms  10.786 ms  13.026 ms
#  3  125.35.86.217  21.995 ms  31.307 ms  31.337 ms
#  4  * * *
#  5  125.33.187.77  27.470 ms  29.682 ms  30.903 ms
#  6  124.65.56.237  38.430 ms  40.342 ms  40.318 ms
#  7  61.148.143.110  52.193 ms  48.893 ms  47.314 ms
#  8  202.106.43.38  53.310 ms  44.386 ms  39.062 ms
#  9  * * *
# 10  * * *
# 11  61.135.169.121  19.172 ms  6.489 ms  6.162 ms
#  
# traceroute -I -n
# -I表示使用icmp协议，-n表示显示ip 
#
# 第一列是序号，也是发送的探测包的ttl的值
# 第二列是网关的ip 
# 其余列三个时间是发送的三个数据包的回包时间，类似icmp时间
# 
# 为什么有的ip的位置是三个星号？
# 因为有的网关设备屏蔽了icmp的ttl为0时的弃包的回应，所以探测不到网关的ip
#
#
# 使用UDP探测：
# sudo traceroute  -n  www.baidu.com
# traceroute to www.baidu.com (61.135.169.125), 30 hops max, 60 byte packets
#  1  192.168.8.1  11.389 ms  11.384 ms  18.947 ms
#  2  192.168.3.1  28.230 ms  28.280 ms  28.372 ms
#  3  125.35.86.217  418.498 ms  553.361 ms  553.374 ms
#  4  * * *
#  5  202.106.37.49  172.409 ms  172.422 ms  172.409 ms
#  6  124.65.60.81  553.171 ms 123.126.7.45  542.201 ms 124.65.57.85  542.109 ms
#  7  123.126.9.138  153.715 ms 61.148.142.142  525.132 ms 202.106.227.10  524.984 ms
#  8  123.125.248.98  144.247 ms 123.125.248.102  380.714 ms 61.49.168.110  380.630 ms
#  9  * * *
# 10  * * *
# 11  * * *
# 12  * * *
# 13  * * *
# 14  * * *
# 15  * * *
# 16  * * *
# 17  * * *
# 18  * * *
# 19  * * *
# 20  * * *
# 21  * * *
# 22  * * *
# 23  * * *
# 24  * * *
# 25  * * *
# 26  * * *
# 27  * * *
# 28  * * *
# 29  * * *
# 30  * * *
#
# 为什么使用udp探测时，无法到达目标主机，产生很多星号，如上所示？
# linux的traceroute默认使用udp，在使用udp时，因为目标主机防火墙的问题，目标主机的
# 超时回包无法正常发回，导致traceroute无法判断是否到达了目标主机，本地会一直增加ttl值
# 发送探测包。
#
# 使用TCP探测：
# sudo traceroute -T  -n  www.baidu.com
# traceroute to www.baidu.com (61.135.169.121), 30 hops max, 60 byte packets
#  1  192.168.8.1  3.998 ms * *
#  2  192.168.3.1  51.368 ms  51.479 ms  51.586 ms
#  3  125.35.86.217  63.315 ms  63.337 ms  63.325 ms
#  4  * * *
#  5  125.33.187.77  58.742 ms  59.915 ms  61.301 ms
#  6  124.65.62.185  64.260 ms 61.51.112.217  62.911 ms *
#  7  61.148.143.110  100.996 ms 124.65.59.214  23.218 ms 61.148.143.110  64.637 ms
#  8  61.49.168.78  29.751 ms  27.334 ms 61.49.168.106  23.252 ms
#  9  * * *
# 10  * 61.135.169.121  21.849 ms  21.861 ms
#
#   -T 表示使用tcp
