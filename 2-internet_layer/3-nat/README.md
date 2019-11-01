NAT(Network Address Translation)网络地址转换  

NAT技术的细节，各个厂家的设备可能都略微有差异，名称上也不太统一。  
从转换地址的角度出发，分析其技术细节，可以将所有的NAT分为SNAT和DNAT。  

SNAT和DNAT。  
SNAT ： 将ip数据包的源地址替换为指定地址。  
DNAT ： 将ip数据包的目的地址替换为指定地址。  
  
SNAT是家用路由器的基本功能，所有的ip数据包经过家用路由器，家用路由器都会将其源地址替换  
为WAN口地址再发送出去。路由器会在本地生成并保存一张ip映射关系表。如果是TCP/UDP协议，还  
会保存port映射关系，如果是icmp协议，会保存identifier映射信息。  
<pre>
nat mapping table
source_ip       source_port       nat_ip         nat_port
192.168.10.10   1000              192.1.1.10     1000
</pre>

思考1：为什么要记录端口号呢？  
在一台pc上，端口的作用是区分tcp/udp包是发给哪个应用程序的，nat记录端口号的目的  
是为了区分tcp/udp回包是发给哪个pc设备的。所以在当源地址不同，源端口相同时，nat  
会改变源端口为另外一个端口。有时，nat会将所有的源端口都改掉，统一规划。  
对于icmp协议，没有port信息，会保存对应的identifier信息，作用是类似的。  

思考2：nat会改变源mac地址吗？  
nat table是不包含mac地址映射关系这一项的，但是nat在解包完数据，转换完成地址和  
端口号后，会将ip数据包重新打包从另一个端口发出，此时，ip协议栈会重新加mac头，  
此时的mac地址自然会被替换为对应接口的mac，所以源mac地址也变了，但是这种变化  
并不是nat直接去改变的。  


<实验：家用路由上网原理>  
家用路由器基本上可以理解为 NAT + 交换机  
简化网络拓扑如下图所示：  
  
|internet| <--> |router-运营商| <--> |switch-运营商| <--> |router-家用|  <--> | pc-家用|  
  
(1)运营商宽带入户，会有一个接口分配到各家各户。  
(2)家用路由器有wan口和lan口之分，各个lan口类似与交换机的各个接口，家用路由器有交换功能，wan口  
有ip地址，用来路由ip数据包。  
  
<pre>
|pc| 源： 192.168.1.10:6688  目的：  220.1.1.10:999  
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
哪个ip地址，会根据本地的nat table去查找对应关系，此时端口号(tcp/udp)和标识符(icmp)就  
很重要了。  
(1)DNAT可以将收到的所有的ip包，全部导向另一台主机。  
(2)DNAT可以将收到的TCP/UDP的指定端口的包，导向另一台主机。