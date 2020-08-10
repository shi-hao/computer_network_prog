# linux ip command tool        
  
<pre>
ip addr/route/rule/xfrm  #IP地址，路由信息，策略路由  
ip neighbor  #ARP表  
ip link    #物理接口  
</pre>
        
## ip addr        
<pre>
(1)查看本地所有网卡IP地址等信息。        
ip addr        
ip addr show        
        
(2)查看本地指定网卡信息。        
ip addr	show dev [device]        
        
(3)增加/删除IP地址信息        
ip addr add ip_addr/mask dev [interface]          
ip addr del ip_addr/mask dev [interface]          
        
ip addr add 192.168.10.10/24 dev eth0          
ip addr del 192.168.10.10/24 dev eth0          
</pre>
        
## ip route        
<pre>
(1)显示内核路由表        
ip route         
ip route show        
        
(2)增加路由        
ip route add dst_ip/mask dev [interface] via [gateway]        
        
ip route add 192.168.0.0/24 dev eno1   #添加静态路由        
ip route add default via 192.168.0.1 dev eno1   #添加默认网关        
ip route add 192.168.200.0/24 dev eno1 via 192.168.0.1  #添加有网关的静态路由        
      
(3)删除路由      
ip route del dst_ip/mask dev [interface] via [gateway]      
      
ip route del 192.168.0.1/24 dev eno1 #删除静态路由      
      
(4)替代路由      
ip route replace dst_ip/mask dev [interface] via [gateway]      
      
(5)获取目标IP地址匹配到的路由      
ip route get dst_ip      
</pre>
      
## ip rule      
<pre>
基于策略的路由(policy based routing)：      
经典的路由算法是根据IP数据包的目的地址字段进行路由，在一些时候，希望能够根据数      
据包的其他字段进行路由，比如源地址，IP协议字段，传输协议端口等，这就是基于策略      
的路由。为了实现基于策略的路由，将原有使用最长匹配规则的路由表替换为策略路由数      
据库(RPDB-routing policy database base)。      
      
RPDB中包含测路路由规则，规则按照优先级从高到低排列，每个规则由selector和action       
predicate组成，selector主要包含源地址，目的地址，入接口，tos，fwmark，如果      
selector匹配数据包，那么执行ation predicate动作，使用ip rule工具对系统RPDB进行      
管理。      
      
内核启动时，创建了3个默认的路由规则，      
Priority: 0, Selector: match anything, Action: lookup routing      
table local (ID 255).  The local table is a special routing      
table containing high priority control routes for local and      
broadcast addresses.      
      
Priority: 32766, Selector: match anything, Action: lookup      
routing table main (ID 254).  The main table is the normal      
routing table containing all non-policy routes. This rule may      
be deleted and/or overridden with other ones by the      
administrator.      
      
Priority: 32767, Selector: match anything, Action: lookup      
routing table default (ID 253).  The default table is empty.      
It is reserved for some post-processing if no previous default      
rules selected the packet.  This rule may also be deleted.      
      
同时也会创建三个路由表，分别对应路由规则中的local，main，default。      
      
(1)查看RPDB路由规则      
ip rule       
ip rule show       

0:	    from all lookup local       
32766:	from all lookup main       
32767:	from all lookup default      
local, main, default是RPDB的三个默认的规则。      
最左侧一栏是规则的优先级，0表示最大，32767最小。      
from all表示IP数据包的源地址为任意地址      
lookup local表示匹配路由表local      

当主机路由数据包时，会逐个匹配RPDB中所有的规则，匹配成功则进行对应操作。        
      
(2)ip rule add/del      
ip rule add/del SELECTOR ACTION      
      
常用SELECTOR：      
from PREFIX         
to PREFIX        
tos TOS       
      
常用ACTION：      
table TABLE_ID       
protocol PROTO        
nat ADDRESS       
      
ip rule add from 192.168.99.0/24 table 10      
表示向策略路由数据库中添加一条规则，来自192.168.99.0网段的数据包，匹配ID为10的      
路由表。      
      
ip route add 192.168.99.0/24 via 192.168.0.1 dev eno1 table 10      
向路由表10中添加路由规则。      
</pre>
    
## ip xfrm     
<pre>
xfrm is an IP framework for transforming packets (such as encrypting    
their payloads). This framework is used to implement the IPsec    
protocol suite (with the state object operating on the Security    
Association Database, and the policy object operating on the Security      
Policy Database). It is also used for the IP Payload Compression     
Protocol and features of Mobile IPv6.    
</pre>
  
## ip neighbor  
<pre>
ip neighbor provides a command line interface to display the neighbor table  
(ARP cache)  
  
查看本地ARP表  
ip neighbor  
ip neighbor show  
  
搜索ARP表  
ip neighbor show [host_ip]  
</pre>
  
## ip link        
<pre>
(1)查看所有物理接口信息        
ip link        
ip link show dev [device]        
      
(2)打开/关闭接口      
ip link set [interface] up/down      
</pre>
