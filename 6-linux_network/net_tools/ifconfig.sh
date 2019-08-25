#!/bin/bash 

# All interface
all_inter=$(ls /sys/class/net)
inter_arr=($all_inter)
len=$((${#inter_arr[*]}-1))

# Echo all interfaces
printf "%-5s %-20s \n" ID Interface
for((i=0;i<=len;i++));
do
	printf "%-5s %-20s \n" $i ${inter_arr[i]}
done 

# Choosing interface
echo -e "\033[31m please inpute 0~$len to choose the interface\033[0m"
read num 

# Interface
my_inter=${inter_arr[$num]}
echo -e "\033[31m interface:$my_inter \033[0m"

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
OLD_IFS=$IFS
IFS=" "
while read line
do 
	arr=($line)
	ip_array+=(${arr[0]})
	mask_array+=(${arr[1]})
	gw_ip+=(${arr[2]})
	msg+=(${arr[3]})
done <$cnf_file
IFS=$OLD_IFS
len=$((${#ip_array[*]}-1))

# Echo all ip mask gw
printf "%-5s%-20s%-20s%-20s%-20s\n" ID IP MASK GW INFO  
for((i=0;i<=len;i++));
do
	echo "_____________________________________________________________________________"
	printf "%-5s%-20s%-20s%-20s%-20s\n" $i ${ip_array[i]}  ${mask_array[i]} ${gw_ip[i]} ${msg[i]}
done 

# Choosing config
echo -e "\033[31m please inpute 0~$len to choose the ip config\033[0m"
read num 
echo "chosing IP:${ip_array[$num]} MASK:${mask_array[$num]} GW:${gw_ip[$num]} INFO:${msg[$num]}"

# Var--ip mask gateway
my_ip=${ip_array[$num]}
my_mask=${mask_array[$num]}
my_gw=${gw_ip[$num]}

# Config the interface ip using cmd
sudo ifconfig $my_inter down
sudo ifconfig $my_inter $my_ip netmask $my_mask
sudo route del default dev $my_inter
sudo route add default gw  $my_gw dev $my_inter

# Check the interface config
ifconfig $my_inter
route -n
ping $my_gw
