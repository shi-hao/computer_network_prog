# Network Topology    
    
<img src="https://github.com/shi-hao/computer_network_prog/blob/master/topology-1.jpg" width="364" height="450" />    
    
## 1.DHCP      
首先，设备PC2，PC3接入到Router-B，PC1和Router-B接入到Router-A，四个设备      
需要通过dhcp协议，分别向Router-B和Router-A请求ip地址。      
<pre>    
	dhcp--discovery      
	dhcp--offer      
	dhcp--request      
	dhcp--ack      
</pre>    
同时dhcp server会向下端推送gateway，dns等信息, DHCP使用UDP协议。      
    
主机在未被分配IP地址之前，如何填充IP，UDP数据包？      
主机会发送广播的IP数据包，自己的IP填充全0，目的IP填充全1，即255.255.255.255。      
    
## 2.本地local计算机通信      
本地的计算机通过交换机相连，当本地同网段计算机通信时，交换机通过MAC地址进行数据包转发。  
这样通信方式效率是最高的。  
  
如何获取目标主机的MAC地址呢？    
首先对端的IP必须是要知道的，然后计算机会通过arp广播包来获取目的IP的mac地址，然后主动发送方    
就可以正常填充ip包头和MAC头，交换机在收到数据包后，直接根据目的MAC转发到相应的接口的计算机。      
  
ARP工作在数据链路层或者说网络层，ARP对下使用以太网协议，不使用IP协议。      
    
### PC2--udp--PC3      
PC2-Server  192.168.3.5:800      
PC3-Client      
    
<pre>    
PC3--发包      
S-MAC:40-77-03-8C-FE-04   S-IP:192.168.3.6  S-PORT:9000      
D-MAC:24-77-03-8C-75-04   D-IP:192.168.3.5  D-PORT:800      
</pre>    
    
因为目的地址和PC3的ip地址在同一网段，首先需要通过arp协议，获取PC2的mac地址。      
获取到mac地址后，如上组包，然后通过网卡发出。      
    
数据包到达Router-B后，因为家用路由器的lan口，相当于交换机，所以直接根据mac地址，      
直接转发到PC2。    
    
<pre>    
PC2--回包      
S-MAC:24-77-03-8C-75-04   S-IP:192.168.3.5  S-PORT:800      
D-MAC:40-77-03-8C-FE-04   D-IP:192.168.3.6  D-PORT:9000      
</pre>    
    
    
## 3.跨网段计算机通信      
NAT工作在网络层，NAT会查看IP数据包和TCP，UDP，ICMP数据包，根据源的IP信息，端口信息，识别码信息      
转换对应的信息。      
    
    
### PC3--udp--PC1      
PC1-Server  192.168.8.113:800      
PC3-Client      
    
PC3      
因为目的ip是跨网域的，PC3根据自己的路由表，ip包会发给网关，所以实际的包内容如下。      
    
<pre>    
S-MAC:40-77-03-8C-FE-04   S-IP:192.168.3.6    S-PORT:9000       
D-MAC:1c-15-1f-46-81-34   D-IP:192.168.8.113  D-PORT:800      
</pre>    
    
数据出去后，根据mac地址，数据发送到网关Router-B，Router-B收到数据后，进行SNAT，       
<pre>    
nat table        
Source                             NAT      
S-IP:192.168.3.6    S-PORT:9000    S-IP:192.168.8.120    S-PORT:9000       
</pre>    
SNAT完毕后，通过哦wan口发送出去，完整的包结构如下。    
    
<pre>    
S-MAC:1c-15-1f-46-81-34   S-IP:192.168.8.120    S-PORT:9000       
D-MAC:00-0e-c6-be-07-23   D-IP:192.168.8.113    D-PORT:800      
</pre>    
    
Router-A收到数据后，直接根据mac地址转发到PC1      
    
<pre>    
PC1--回包      
S-MAC:00-0e-c6-be-07-23    S-IP:192.168.8.113    S-PORT:800       
D-MAC:1c-15-1f-46-81-34    D-IP:192.168.8.120    D-PORT:9000        
</pre>    
    
Router-A收到数据后，直接根据mac地址转发到Router-B，Router-B根据收到数据的port号，      
查询自己的nat table，进行DNAT操作。      
<pre>    
nat table        
D-IP:192.168.8.120    D-PORT:9000 -->  D-IP:192.168.3.6    D-PORT:9000     
</pre>    
转换完毕后，Router-B查询自己的route table，arp table将数据包发送出去，完整的      
包结构如下。      
<pre>    
S-MAC:1c-15-1f-46-81-34    S-IP:192.168.8.113    S-PORT:800       
D-MAC:40-77-03-8C-FE-04    D-IP:192.168.3.6      D-PORT:9000        
</pre>    
通过以上，可以看到nat主要改变ip头，tcp/udp，icmp包中的数据。经过路由器的数据      
的源mac地址都会被路由器的mac替换。      
    
    
**NAT如何处理ICMP包？**    
ICMP包中有和TCP/UDP端口号类似的域，NAT会使用这个域进行转化。    
  
**局域网内IP地址相同对网络的影响？**    
两台主机，不同的MAC地址，相同的IP地址，污染网络内其他设备的arp表。   

首先，会污染局域网内其他主机的arp表，当其他的主机试图与该IP地址进行通信时，两台主机  
会同时回应arp数据包，其他主机可能只会接受一个mac地址，或者两个都不接受。  

其次，会污染网关路由的arp表，当两台主机通过网关与外界通信时，nat逆向回包时，无法返回
给正确的主机。
