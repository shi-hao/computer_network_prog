#!/bin/bash 

# interface
my_inter="enp0s31f6"

# ip mask gateway array 
ip_array=("11.15.244.63" "192.168.8.192")
mask_array=("255.255.255.0" "255.255.255.0")
gw_ip=("11.15.244.254" "192.168.8.1")
msg=("白石桥AS" "local")

len=$((${#ip_array[*]}-1))

echo -en "ip \t mask \t gw \t info \n"
for((i=0;i<=len;i++));
do
	echo -en "${ip_array[i]} \t  ${mask_array[i]} \t ${gw_ip[i]} \t  ${msg[i]} \n"
done 

echo -e "\033[31m please inpute 0-$len to choose the ip config\033[0m"
read num 
echo "choosing ip:${ip_array[$num]}  mask:${mask_array[$num]}  gw:${gw_ip[$num]}"

my_ip=${ip_array[$num]}
my_mask=${mask_array[$num]}
my_gw=${gw_ip[$num]}

#config the interface ip using cmd
sudo ifconfig $my_inter down
sudo ifconfig $my_inter $my_ip netmask $my_mask
sudo route add default gw  $my_gw  $my_inter
sudo ifconfig $my_inter up

#checkt the interface config
ifconfig $my_inter
route -n
ping $my_gw