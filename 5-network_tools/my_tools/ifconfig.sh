#!/bin/bash 

# Adding dns config??

source ./my_function.sh

# Trap ctrl-c
my_break

# Chose network interface
chose_if my_if

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

# Config file
cnf_file=/home/bleach/myfile/ip_cnf.txt

# Read ip mask gateway
while read line
do 
	arr=($line)
	ip_array+=(${arr[0]})
	mask_array+=(${arr[1]})
	gw_ip+=(${arr[2]})
	msg+=(${arr[3]})
done <$cnf_file
len=$((${#ip_array[*]}-1))

# Echo all ip mask gw
my_printf "green" "null" "ID" "IP" "MASK" "GW" "INFO" 
for((i=0;i<=len;i++));
do
	my_printf "null" "line" $i ${ip_array[i]}  ${mask_array[i]} ${gw_ip[i]} ${msg[i]}
done 

# Choosing config
in_id=""
while [[ ! "$in_id" =~ ^[0-9]+$ || $in_id -gt $len || $in_id -lt 0 ]]; do
	my_echo "red" " please input 0~$len to chose the ip config"
	read in_id
done
my_echo "red" " chosing IP:${ip_array[$in_id]} MASK:${mask_array[$in_id]} GW:${gw_ip[$in_id]} INFO:${msg[$in_id]}"

# Var--ip mask gateway
my_ip=${ip_array[$in_id]}
my_mask=${mask_array[$in_id]}
my_gw=${gw_ip[$in_id]}

# Config the interface ip using commands
#sudo ifconfig $my_if down
sudo ifconfig $my_if $my_ip netmask $my_mask
sudo route del default dev $my_if
sudo route add default gw  $my_gw dev $my_if

# Check the interface config
ifconfig $my_if
route -n
ping $my_gw
