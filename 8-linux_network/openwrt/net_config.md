# OpenWRT Network Config

## OpenWRT Interface Config
OpenWRT network interface config file is "/etc/config/network",
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
	option type 'bridge'           #config bridge
	option ifname 'eth1 eth0'      #config 2 interface, eth0,eth1
	option force_link '1'
	option proto 'static'
	option ipaddr '192.168.100.2'  #bridge ip
	option netmask '255.255.255.0' #im mask
	option ip6assign '60'
	option multicast_querier '0'
	option igmp_snooping '0'
	option macaddr '00:aa:bb:cc:dd:10' #mac address

config device 'lan_dev'
	option name 'eth1'
	option macaddr '00:aa:bb:cc:dd:10'

#####################config WAN
config interface 'wan'
	option ifname 'eth0'
	option proto 'dhcp'
	option macaddr '00:aa:bb:cc:dd:11'

config device 'wan_dev'
	option name 'eth0'
	option macaddr '00:aa:bb:cc:dd:11'

config interface 'wan6'
	option ifname 'eth0'
	option proto 'dhcpv6'
</pre>

## OpenWRT DHCP 

## OpenWRT Firewall
