#!/bin/bash 

# Interface
#my_inter="wlp4s0"
my_inter="enp0s31f6"
#my_inter="enx000ec6be0723"
echo -e "\033[31m interface:$my_inter \033[0m"

# Del the default gateway
if [ "$1" == "clear" ] ;then
	sudo route del default dev $my_inter
	echo "route del default dev $my_inter"
	exit 0
fi

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
done </home/bleach/myfile/ip_cnf.txt
IFS=$OLD_IFS
len=$((${#ip_array[*]}-1))

# Echo all ip mask gw
echo -en "ID \t IP \t MASK \t GW \t INFO \n"
for((i=0;i<=len;i++));
do
	echo -en "[$i] \t ${ip_array[i]} \t ${mask_array[i]} \t ${gw_ip[i]} \t ${msg[i]} \n"
done 

# Choosing config
echo -e "\033[31m please inpute 0~$len to choose the ip config\033[0m"
read num 
echo "choosing ip:${ip_array[$num]}  mask:${mask_array[$num]}  gw:${gw_ip[$num]}"

#
my_ip=${ip_array[$num]}
my_mask=${mask_array[$num]}
my_gw=${gw_ip[$num]}

# Config the interface ip using cmd
sudo ifconfig $my_inter down
sudo ifconfig $my_inter $my_ip netmask $my_mask
sudo route del default dev $my_inter
sudo route add default gw  $my_gw dev $my_inter
#sudo ifconfig $my_inter up

# Check the interface config
ifconfig $my_inter
route -n
ping $my_gw
