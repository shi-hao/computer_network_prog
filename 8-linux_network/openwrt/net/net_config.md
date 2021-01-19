# OpenWRT Network Config  
  
## OpenWRT Interface Config  
OpenWRT network interface config file is "/etc/config/network"  
  
option gateway '192.168.100.1'  
This config item will create a default gateway in local route table.  
  
<pre>  
config interface 'loopback'  
	option ifname 'lo'  
	option proto 'static'  
	option ipaddr '127.0.0.1'  
	option netmask '255.0.0.0'  
  
config globals 'globals'  
	option ula_prefix 'auto'  
  
#####################config LAN  
config interface 'lan'             #config lan  
	option type 'bridge'           #set lan type to bridge  
	option ifname 'eth1 eth0'      #lan contains two ethernet interface 'eth0 eth1'  
	option force_link '1'  
	option proto 'static'  
	option ipaddr '192.168.100.2'  #set bridge ip  
	option netmask '255.255.255.0' #set ip mask  
	option gateway '192.168.100.1' #set local default gateway  
	option ip6assign '60'  
	option multicast_querier '0'  
	option igmp_snooping '0'  
	option macaddr '00:aa:bb:cc:dd:10' #set bridge mac address  
  
config device 'lan_dev'    #set device   
	option name 'eth1'  
	option macaddr '00:aa:bb:cc:dd:10' #set eth1 mac address  
  
#####################config WAN  
config interface 'wan'  
	option ifname 'eth0' #set eth0 as wan  
	option proto 'dhcp'  #enable dhcp client in eth0  
	option macaddr '00:aa:bb:cc:dd:11' #set mac address   
  
config device 'wan_dev'  #set device  
	option name 'eth0'  
	option macaddr '00:aa:bb:cc:dd:11'  
  
config interface 'wan6'   #set ipv6 wan  
	option ifname 'eth0'  #set eth0 as wan6  
	option proto 'dhcpv6' #enable dhcpv6   
</pre>  
  
## OpenWRT DHCP   
OpenWRT DHCP Server config file is "/etc/config/dhcp"  
	  
list dhcp_option '3,192.168.1.1'  
Using the dhcp option 3 to push default gateway to all the dhcp clients.  
  
list dhcp_option '121,192.168.0.0∕16,192.168.1.1'  
Using the dhcp option 121 to push a static gateway to all the dhcp clients.  
  
<pre>  
config dnsmasq  
	option domainneeded '1'  
	option boguspriv '1'  
	option filterwin2k '0'  
	option localise_queries '1'  
	option rebind_protection '1'  
	option rebind_localhost '1'  
	option local '∕example.com∕'  
	option domain 'example.com'  
	option expandhosts '1'  
	option nonegcache '0'  
	option authoritative '1'  
	option readethers '1'  
	option leasefile '∕tmp∕dhcp.leases'  
	option resolvfile '∕tmp∕resolv.conf.auto'  
	option server '192.168.1.1' # Upstream DNS.  
  
config dhcp 'lan'  
	option interface 'lan' #enable dhcp server in 'lan'  
	option start '1'       #set the dhcp ip poll start to 1  
	option limit '100'     #set the dhcp ip poll limit to 100  
	option leasetime '12h' #set ip lease time to 12 hours  
	option dhcpv6 'server' #enable dhcpv6  
	option ra 'server'  
	list dhcp_option '3,192.168.1.1' #set the default gateway  
	list dhcp_option '121,192.168.0.0∕16,192.168.1.1' #set a static route  
  
config dhcp 'wan'  
	option interface 'wan'  
	option ignore '1'  
	config odhcpd 'odhcpd'  
	option maindhcp '0'  
	option leasefile '∕tmp∕hosts∕odhcpd'  
	option leasetrigger '∕usr∕sbin∕odhcpd-update'  
	config host  
	option name 'server.example.com'  
	option ip '192.168.1.101'  
	option mac 'aa:bb:cc:dd:ee:ff'  
</pre>  
  
  
## OpenWRT Firewall  
OpenWRT DHCP Server config file is "/etc/config/firewall"  

enable ip forward
enbale masquerade on interface

iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE
