# PPTP          
点对点隧道协议（英语：Point to Point Tunneling Protocol，缩写为PPTP）是实现虚拟专用网（VPN）的方式之一。     
PPTP使用传输控制协议（TCP，1723端口）创建控制通道来发送控制命令，以及利用通用路由封装（GRE）通道来封装点      
对点协议（PPP）数据包以发送数据。这个协议最早由微软等厂商主导开发，但因为它的加密方式容易被破解，微软已经      
不再建议使用这个协议。       
PPTP协议只有简单的协议安全机制，没有类似SSL VPN的认证加密机制。    
    
## 建立连接流程  
1. 建立TCP连接，目的端口1723  
2. 发送PPTP控制数据包，建立控制信道。  
3. 通过IP协议承载PPP协议数据包，发送数据。   
  
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
  
  
  
## ubuntu16配置pptp服务          
1.安装pptp服务          
sudo apt-get update           
sudo apt-get install pptpd          
          
          
2.修改pptpd设置          
sudo vi /etc/pptpd.conf          
          
<pre>          
option   /etc/ppp/pptpd-option    #指定PPP选项文件的位置          
debug                             #启用调试模式          
localip  192.168.10.1             #VPN服务器的虚拟ip          
remoteip 192.168.10.100-200       #分配给VPN客户端的虚拟ip          
</pre>          
          
3.编辑用户配置文件添加用户          
sudo vi /etc/ppp/chap-secrets          
        
<pre>          
# Secrets for authentication using CHAP          
# client    server   secret    IP addresses          
testvpn1    pptpd    test123   *          
</pre>          
其中testvpn1是用户名，pptpd表示是pptpd服务，test123是密码,星号表示随机分配ip          
          
4.修改ppp选项配置文件配置dns          
sudo vi /etc/ppp/pptpd-options          
        
<pre>          
ms-dns 8.8.8.8          
ms-dns 114.114.114.114          
</pre>          
          
5.重启pptpd服务          
<pre>          
service pptpd restart          
</pre>          
          
验证pptp服务是否在运行：          
<pre>          
netstat -alpn | grep :1723          
</pre>          
        
6.开启ip数据包转发        
sudo vim /etc/sysctl.conf         
        
<pre>        
net.ipv4.ip_forward=1        
</pre>        
命令行启动转发        
<pre>        
sudo sysctl -p        
</pre>        
          
7.修改iptable NAT转发          
<pre>          
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE && iptables-save          
</pre>          
系统重启后，iptables规则没有保存，待解决！！    
          
      
## Win10连接PPTP服务器      
网络->VPN->添加VPN      
      
## Android连接PPTP服务器      
设置->无线和网络->VPN      
          
## troubleshooting    
win10连接上pptp服务后，百度竟然无法访问，可以访问其他网站！！          
暂时没有解决这个问题！！          
