NAT(Network Address Translation)网络地址转换    
  
**SNAT/DNAT**  
**NAT Mapping Table**  
  
NAT技术的细节，各个厂家的设备可能都略微有差异，名称上也不太统一。    
简单来说，可以将所有的NAT分为SNAT和DNAT。    
  
SNAT ： 将ip数据包的源地址替换为指定地址。    
DNAT ： 将ip数据包的目的地址替换为指定地址。    
  
SNAT是路由器很基础的功能，当路由器收到内网的TCP/UDP数据包时，会将收到数据包的源地址  
更改为外网端口的IP地址，然后通过指定接口转发出去，并将端口信息填入NAT映射表。  
当路由器收到远端的主机回复数据时，路由器会进行DNAT操作，通过查询NAT映射表，  
将目的IP地址转换为内网的主机地址，并通过指定接口转发出去。  
    
SNAT Mapping Table    
<pre>  
NAT Mapping Table  
source_ip       source_port       NAT_ip         NAT_port  
192.168.10.10   1000              192.1.1.10     1000  
</pre>  
  
DNAT Mapping Table    
<pre>  
NAT Mapping Table  
destination_ip  destination_port  NAT_ip         NAT_port  
192.1.1.10      1000              192.168.10.10  1000  
</pre>  
  
思考1：为什么要NAT？  
NAT解决了公网IP地址不足的问题，通过NAT，多台主机可以共享一个IP地址来访问其  
他网段，核心思想是将TCP/UDP端口号分配给其他主机。  
NAT一定程度上页增强了网络安全性，可以仅仅暴露内网一台主机的指定TCP端口到外网。  
  
思考2：为什么要记录端口号呢？    
在一台PC上，端口的作用是区分TCP/UDP包是发给哪个应用程序的，NAT记录端口号的目的    
是为了区分TCP/UDP回包是发给哪个PC设备的。所以在当源地址不同，源端口相同时，NAT    
会改变源端口为另外一个端口。有时，NAT会将所有的源端口都改掉，统一规划。    
  
思考3：NAT会改变源mac地址吗？    
NAT table是不包含mac地址映射关系这一项的，但是NAT转换完地址和端口号后，会将ip数    
据包重新打包从另一个端口发出，此时，ip协议栈会重新加mac头，此时的mac地址自然会    
被替换为对应接口的mac，所以源mac地址也变了，但是这种变化并不是NAT直接去改变的。      
  
思考4：NAT兼容ICMP协议吗？  
NAT对使用TCP/UDP的协议有很好的兼容性，但是ICMP不使用TCP/UDP，NAT是否兼容呢？  
在ICMP协议字段中，有根端口号类似的字段，即identifier字段，这个字段可以起到和  
端口号相同的功能，所以，NAT是兼容ICMP协议的。  
  
<实验：家用路由上网原理>    
家用路由器基本上可以理解为 NAT + 交换机    
简化网络拓扑如下图所示：    
    
|internet| <--> |router-运营商| <--> |switch-运营商| <--> |router-家用|  <--> | PC-家用|    
    
(1)运营商宽带入户，会有一个接口分配到各家各户。    
(2)家用路由器有wan口和lan口之分，各个lan口类似与交换机的各个接口，家用路由器有交换功能，wan口    
有ip地址，用来路由ip数据包。    
    
<pre>  
|PC| 源： 192.168.1.10:6688  目的：  220.1.1.10:999    
 ||    
 \/    
|lan interface|    
|  router B   |  路由B将收到的ip数据包的源地址转换为自己的wan口地址    
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
  
DNAT是路由网关的经典功能，简单来说，就是替换收到的ip数据包的目的地址为指定的地址。改变为    
哪个ip地址，会根据本地的NAT table去查找对应关系，此时端口号(TCP/UDP)和标识符(ICMP)就    
很重要了。    
(1)DNAT可以将收到的所有的ip包，全部导向另一台主机。    
(2)DNAT可以将收到的TCP/UDP的指定端口的包，导向另一台主机。  
