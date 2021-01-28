# tcpdump   
tcpdump is a data-network packet analyzer computer program that runs under a  
command line interface. It allows the user to display TCP/IP and other packets  
being transmitted or received over a network to which the computer is  
attached.[3] Distributed under the BSD license,[4] tcpdump is free software.   
          
-i [interface]          
指定网卡接口  
  
-v  
-vv  
-vvv  
-vvvn  
详细输出抓包结果  
-n显示IP地址而非主机名  
  
-w [file_name]  
保存抓包数据到文件  
  
host  [ip]  
过滤IP包，指定抓包的ip地址，即只输出ip地址为指定地址的数据包。  
  
port  [number]  
过滤IP包，指定IP包的端口号。  
  
tcp/udp/arp/icmp  
过滤协议  
