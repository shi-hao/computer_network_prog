NAT(Network Address Translation)网络地址转换  

NAT主要类型：

Static NAT is used to do a one-to-one mapping between an inside address and an outside address. 
Static NAT also allows connections from an outside host to an inside host. 
Usually, static NAT is used for servers inside your network. For example, you may have a web 
server with the inside IP address 192.168.0.10 and you want it to be accessible when a 
remote host makes a request to 209.165.200.10. For  this to work, you must do a static NAT 
mapping between those to IPs. 
静态NAT，将一个内网地址映射为一个外网地址，主要用于WEB服务器，比如一台内部的WEB服务器需要被
外网访问，可以通过NAT设置将其暴露到外网。
举例说明：
一台内网服务器ip-192.168.1.100，和网关路由的接口0相连，ip-192.168.1.1，网关的外网接口1的公网
地址为20.10.10.9，通过静态NAT，将地址192.168.1.100映射为20.10.10.9，那么外网所有的以ip为
20.10.10.9的ip数据包，都会被网关路由转换地址后发给服务器192.168.1.100


Dynamic NAT is used when you have a “pool” of public IP addresses that you want to assign 
to your internal hosts dynamically. Don’t use dynamic NAT for servers or other devices that 
need to be accessible from the Internet.

NAT Overload, sometimes also called PAT(Port Addresses Translation), is probably the most 
used type of NAT.



Static NAT (Network Address Translation) 
Static NAT (Network Address Translation)is one-to-one mapping of a private IP address to 
a public IP address. Static NAT (Network Address Translation) is useful when a network 
device inside a private network needs to be accessible from internet.






  
SNAT和DNAT。  
SNAT ： 将ip数据包的源地址替换为指定地址。  
DNAT ： 将ip数据包的目的地址替换为指定地址。  
  
SNAT是家用路由器的基本功能，所有的ip数据包经过家用路由器，家用路由器都会将其源地址替换  
为WAN口地址再发送出去。  
  
???nat 端口号 映射吗？？？？？  
  
<家用路由上网原理>  
家用路由器基本上可以理解为 NAT + 交换机  
简化网络拓扑如下图所示：  
  
|internet| <--> |router-运营商| <--> |switch-运营商| <--> |router-家用|  <--> | pc-家用|  
  
(1)运营商宽带入户，会有一个接口分配到各家各户。  
(2)家用路由器有wan口和lan口之分，各个lan口类似与交换机的各个接口，说明家用路由器有交换功能，wan口  
有ip地址，用来路由ip数据包。  
  
<pre>
|pc| 源： 192.168.1.10:6688  目的：  220.1.1.10:999  
 ||  
 \/  
|lan interface|  
|  router B   |  路由B将收到的ip数据包的源地址转换为自己的wan口地址，将源端口号转换为新的端口号。  
|wan interface|  S-192.168.1.10:6688 D-220.1.1.10:999  -->  S-192.1.1.20:9999  D-220.1.1.10:999  
 ||  
 \/  
|switch A|  
 ||  
 \/  
|interface 1| ip-192.1.1.1  
|router A   |  
|interface 2|  
</pre>
