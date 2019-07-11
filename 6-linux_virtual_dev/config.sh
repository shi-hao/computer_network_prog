#!/bin/bash 

#config the interface

#ifconfig [interface]  up/down  打开关闭网卡
#ifconfig [interface] [ip] netmask [mask]  设置网卡ip及其掩码
ifconfig enp0s31f6 down 
ifconfig enp0s31f6 11.15.244.64 netmask 255.255.255.0 
ifconfig enp0s31f6 up


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
