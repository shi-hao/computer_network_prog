#!/bin/bash 

# ip mask gw 
ip_array=("11.15.244.63" "192.168.1.192")
mask_array=("255.255.255.0" "255.255.255.0")
gw_ip=("11.15.244.254" "192.168.1.1")

len=${#ip_array[*]}

echo "please inpute 0-$len to choose the ip config"
echo "ip  : ${ip_array[*]}"
echo "mask: ${mask_array[*]}"
echo "gw  : ${gw_ip[*]}"

read num 

echo "choosing ip:${ip_array[$num]}  mask:${mask_array[$num]}  gw:${gw_ip[$num]}"

#config the interface ip using cmd
sudo ifconfig enp0s31f6 down
sudo ifconfig enp0s31f6 11.15.244.63 netmask 255.255.255.0 
sudo route add default gw 11.15.244.254  enp0s31f6
sudo ifconfig enp0s31f6 up

