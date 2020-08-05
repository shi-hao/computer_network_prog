# linux ip command tool  
修改查看设备IP地址，路由信息，策略路由，ARP表  
  
## ip addr  
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
  
## ip link  
(1)查看所有物理接口信息  
ip link  
ip link show dev [device]  

(2)打开/关闭接口
ip link set [interface] up/down
  
## ip route  
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

## ip rule
routing policy database base(RPDB)，是linux的路由策略数据库，可以使用ip rule名
利查看管理RPDB。
(1)ip rule show
ip rule 
ip rule show 
<pre>
0:	    from all lookup local 
32766:	from all lookup main 
32767:	from all lookup default
</pre>
local, main, default是RPDB的三个默认的规则，最左侧一栏是规则的优先级，0表示最
大，32767最小。
所有的IP数据包必须先匹配local规则中的路由表，local规则中的路由表主要是广播地址，
NAT地址转换，本地IP地址。  
当主机路由数据包时，会逐个匹配RPDB中所有规则中的路由表，直至匹配成功。  

(2)ip rule add
