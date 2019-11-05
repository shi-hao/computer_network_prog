#!/bin/bash 

# Adding dns config??

source ./base.sh

# Trap ctrl-c
trap 'echo "exit ping"; exit' INT

# Get all interfaces
all_inter=$(ls /sys/class/net)
inter_arr=($all_inter)
len=$((${#inter_arr[*]}-1))

# Echo all interfaces
printf_2_yell "ID" "Interface"
for((i=0;i<=len;i++));
do
	printf_2_default $i ${inter_arr[i]}
done 

# Chosing interface
echo_red "please inpute 0~$len to chose the interface"
read num 

# Interface
my_inter=${inter_arr[$num]}
echo_red "interface:$my_inter "

# Del the default gateway
if [ "$1" == "clear" ] ;then
	sudo route del default dev $my_inter
	echo "route del default dev $my_inter"
	route -n
	exit 0
fi

# DHCP
if [ "$1" == "dhcp" ] ;then
	sudo dhclient -r $my_inter
	sudo dhclient $my_inter

	ifconfig $my_inter
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
printf_5_yell "ID" "IP" "MASK" "GW" "INFO" 
for((i=0;i<=len;i++));
do
	printf_5_under_line $i ${ip_array[i]}  ${mask_array[i]} ${gw_ip[i]} ${msg[i]}
done 

# Chosing config
echo_red " please inpute 0~$len to chose the ip config"
read num 
echo_red "chosing IP:${ip_array[$num]} MASK:${mask_array[$num]} GW:${gw_ip[$num]} INFO:${msg[$num]}"

# Var--ip mask gateway
my_ip=${ip_array[$num]}
my_mask=${mask_array[$num]}
my_gw=${gw_ip[$num]}

# Config the interface ip using commands
sudo ifconfig $my_inter down
sudo ifconfig $my_inter $my_ip netmask $my_mask
sudo route del default dev $my_inter
sudo route add default gw  $my_gw dev $my_inter

# Check the interface config
ifconfig $my_inter
route -n
ping $my_gw
