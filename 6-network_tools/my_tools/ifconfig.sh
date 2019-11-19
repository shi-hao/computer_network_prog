#!/bin/bash 

# Adding dns config??

source ./my_function.sh

# Trap ctrl-c
trap 'echo -e "\n exit \n"; exit' INT

# Get all interfaces
all_ifs=$(get_if_names)
ifs_arr=($all_ifs)
len=$((${#ifs_arr[*]}-1))

# Echo all interfaces
my_printf "green" "null" "ID" "Interface" "IP" "MAC"
for((i=0;i<=len;i++));
do
	card_ip=$(get_card_ip "${ifs_arr[i]}")
	card_mac=$(get_card_mac "${ifs_arr[i]}")
	my_printf "null" "null" "$i" "${ifs_arr[i]}" "$card_ip" "$card_mac"
done 

# Chosing interface
my_echo "red" " please inpute 0~$len to chose the interface"
read num 
if (( $num > $len )) || (( $num < 0 ));then 
	my_echo "red" " inpute error, exit!"
	exit
fi

# Interface
my_if=${ifs_arr[$num]}
my_echo "red" " chosing interface:$my_if "

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

# Chosing config
my_echo "red" " please inpute 0~$len to chose the ip config"
read num 
if (( $num > $len )) || (( $num < 0 ));then 
	my_echo "red" " inpute error, exit!"
	exit
fi
my_echo "red" " chosing IP:${ip_array[$num]} MASK:${mask_array[$num]} GW:${gw_ip[$num]} INFO:${msg[$num]}"

# Var--ip mask gateway
my_ip=${ip_array[$num]}
my_mask=${mask_array[$num]}
my_gw=${gw_ip[$num]}

# Config the interface ip using commands
sudo ifconfig $my_if down
sudo ifconfig $my_if $my_ip netmask $my_mask
sudo route del default dev $my_if
sudo route add default gw  $my_gw dev $my_if

# Check the interface config
ifconfig $my_if
route -n
ping $my_gw
