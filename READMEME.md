# network topology

<img src="https://github.com/shi-hao/computer_network_prog/blob/master/topology-1.jpg" width="364" height="450" />

1.DHCP  
首先，设备PC2，PC3接入到Router-B，PC1和Router-B接入到Router-A，四个设备  
需要通过dhcp协议，分别向Router-B和Router-A请求ip地址。  
dhcp--discovery  
dhcp--offer  
dhcp--request  
dhcp--ack  
同时dhcp server会向下端推送gateway，dns等信息。  

2.PC2--udp--PC3  
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


3.PC3--udp--PC1  
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
S                                  NAT  
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
