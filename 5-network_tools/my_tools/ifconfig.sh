#!/bin/bash 

# Adding dns config??

source my_cnf.sh
source my_ifs.sh
source my_stdio.sh

# Config file
cnf_file=/home/bleach/myfile/ip_cnf.txt

################################################
# Trap ctrl-c
my_break

# Choose network interface
pick_if my_if

# Del the default gateway
if [ "$1" == "clear" ] ;then
	sudo route del default dev $my_if
	my_echo "red" "route del default dev $my_if"
	route -n
	exit 0
fi

# DHCP
if [ "$1" == "dhcp" ] ;then
	sudo dhclient -r $my_if
	sudo dhclient $my_if

	ifconfig $my_if
	route -n
	exit 0
fi

# choose config items
pick_int_cnf $cnf_file my_ip my_mask my_gw

# Config the interface ip using commands
#sudo ifconfig $my_if down
sudo ifconfig $my_if $my_ip netmask $my_mask
sudo route del default dev $my_if
sudo route add default gw  $my_gw dev $my_if

# Check the interface config
ifconfig $my_if
route -n
ping $my_gw
################################################
