# Setting up an Ethernet Interface

The majority of network setup can be done via the interfaces configuration
file at /etc/network/interfaces. Here, you can give your network card an IP
address (or use dhcp), set up routing information, configure IP masquerading,
set default routes and much more. 

Remember to add interfaces that you want brought up at boot time to the 'auto'
line. 


## Bridging
Bridging puts multiple interfaces into the same network segment. This is very
popular when connecting a server to multiple switches for high availability or
with virtualization. In the latter case it is usually used to create a bridge
in the host (eg. dom0) and put the virtual interfaces of the guests (domU)
into the bridge.

Example: Connect a server to 2 switches (via eth0 and eth1) by defining bridge
0 and give the server an IP address in this subnet:

auto br0
iface br0 inet static
	address 10.10.0.15/24
	gateway 10.10.0.1
	bridge_ports eth0 eth1
	up /usr/sbin/brctl stp br0 on
