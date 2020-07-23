# PPTP                  
    
## 1.What is PPTP and used for?    
PPTP:Point to Point Tunneling Protocol，点到点隧道协议    
Designed as an extension of PPP, PPTP encapsulates PPP packets for    
transmission over IP.    
    
## 2.Packet    
PPTP报文格式如下所示:          
<pre>          
              2byte             +             2byte               
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|             Length            |       PPTP Message Type       |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|                         Magic Cookie                          |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|     Control Message Type      |           Reserved0           |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|       Protocol Version        |           Reserved1           |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|                     Framing Capabilities                      |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|                      Bearer Capabilities                      |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|       Maximum Channels        |       Firmware Revision       |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|                                                               |          
+                     Host Name (64 octets)                     +          
|                                                               |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
|                                                               |          
+                   Vendor String (64 octets)                   +          
|                                                               |          
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+          
</pre>          
        
GRE报文格式如下所示：        
<pre>        
--------------------------------------------------------        
|2bytes                                 |2bytes        |        
|Bits 0–4   5–7     8   9-12    13–15   |16–31         |        
---------------------------------------------------------        
|C R K S s  Recur   A   Flags   Version | Protocol Type|        
---------------------------------------------------------        
|Key Payload Length                     | Key Call ID  |        
---------------------------------------------------------        
|                  Sequence Number (optional)          |        
---------------------------------------------------------        
|                  Acknowledgement Number (optional)   |        
---------------------------------------------------------        
</pre>        
        
PPP报文格式    
<pre>        
-----------------------------------------------------------------------------------        
|Name                   Number of bytes         Description        
-----------------------------------------------------------------------------------        
|Flag                   1                       0x7E, the beginning of a PPP frame        
|Address                1                       0xFF, standard broadcast address        
|Control                1                       0x03, unnumbered data        
|Protocol               2                       PPP ID of embedded data        
|Information            variable (0 or more)    datagram        
|Padding                variable (0 or more)    optional padding        
|Frame Check Sequence   2                       frame checksum        
|Flag                   1                       0x7E, omitted for successive PPP packets         
-----------------------------------------------------------------------------------        
</pre>        
        
## 3.Sequence    
(1)使用TCP协议，目的端口1723，发送PPTP控制数据包，建立控制信道。          
	ip_header + tcp_header + pptp_header        
(2)使用IP协议，IP协议类型47，承载GRE协议数据包，GRE承载PPP协议数据包，发送数据。           
	ip_header + gre_header + ppp         
  
**GRE兼容NAT问题**  
因为GRE和NAT存在兼容问题，如果PPTP的客户端在NAT设备之后，那么NAT网关后的网域内  
只能有一台主机和Server正常通信，因为GRE字段内没有类似端口号的字段，无法通过NAT  
映射来区分不同的主机。  
    
**虚拟网卡技术**          
PPTP客户端服务端通过TCP，GRE建立数据隧道，然后在客户端服务端生成虚拟网卡，将隧道入口打开，      
通过修改系统的路由表，将其他应用程序的数据导入到虚拟网卡，其他应用程序数据就可以通过数据      
隧道传输，客户端和服务端会生成一个名字为pptpd的虚拟网卡！      
          
## 4.Application          
### ubuntu16配置pptp服务                  
(1)安装pptp服务                  
<pre>                  
sudo apt-get update                   
sudo apt-get install pptpd                  
</pre>                  
                  
                  
(2)修改pptpd设置                  
sudo vi /etc/pptpd.conf                  
                  
<pre>                  
option   /etc/ppp/pptpd-option    #指定PPP选项文件的位置                  
debug                             #启用调试模式                  
localip  192.168.10.1             #VPN服务器的虚拟ip                  
remoteip 192.168.10.100-200       #分配给VPN客户端的虚拟ip                  
</pre>                  
                  
(3)编辑用户配置文件添加用户                  
sudo vi /etc/ppp/chap-secrets                  
                
<pre>                  
# Secrets for authentication using CHAP                  
# client    server   secret    IP addresses                  
testvpn1    pptpd    test123   *                  
</pre>                  
其中testvpn1是用户名，pptpd表示是pptpd服务，test123是密码,星号表示随机分配ip                  
                  
(4)修改ppp选项配置文件配置dns                  
sudo vi /etc/ppp/pptpd-options                  
                
<pre>                  
ms-dns 8.8.8.8                  
ms-dns 114.114.114.114                  
</pre>                  
                  
(5)重启pptpd服务                  
<pre>                  
service pptpd restart                  
</pre>                  
                  
验证pptp服务是否在运行：                  
<pre>                  
netstat -alpn | grep :1723                  
</pre>                  
                
(6)开启ip数据包转发                
sudo vim /etc/sysctl.conf                 
                
<pre>                
net.ipv4.ip_forward=1                
</pre>                
命令行启动转发                
<pre>                
sudo sysctl -p                
</pre>                
                  
(7)修改iptable NAT转发                  
<pre>                  
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE && iptables-save                  
</pre>                  
系统重启后，iptables规则没有保存，待解决！！            
              
### Win10连接PPTP服务器              
网络->VPN->添加VPN              
              
### Android连接PPTP服务器              
设置->无线和网络->VPN              
                  
## troubleshooting            
win10连接上pptp服务后，百度竟然无法访问，可以访问其他网站！！                  
暂时没有解决这个问题！！                  
