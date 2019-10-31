#!/bin/bash 

while read line
do  
eval "$line"  
done < des_ip.txt  

echo "目标主机ip为$host_ip"
echo "目标主机网关为$gateway"
echo "目标主机TCP端口为$tcp_port"
echo "目标主机UDP端口为$udp_port"

while true
do
	isContinue='y'
	read -p 'continue? [y/n]' isContinue
	echo $isContinue
	
	if [ $isContinue == 'y' ]; then
		break
	fi
done
