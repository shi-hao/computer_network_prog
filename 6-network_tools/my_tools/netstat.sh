#!/bin/bash 

#pause function
pause(){
	while true
	do
		isContinue='y'
		read -p 'continue? [y/n]' isContinue
		if [ "$isContinue" == "y" ]; then
			break
		fi
	done
}

while read line
do  
eval "$line"  
done < des_ip.txt  

echo "----------------------------------"
echo "目标主机ip为$host_ip"
echo "目标主机网关为$gateway"
echo "目标主机traceroute协议为$tracert_pro"
echo "目标主机TCP端口为$nmap_tcp_port"
echo "目标主机UDP端口为$nmap_udp_port"
echo "----------------------------------"

pause

echo "step1：查看本地网卡和路由配置"

ifconfig 
route -n

pause

echo "step2：ping主机"
if [ -n "$gateway" ];
then
	ping  -c 5 $gateway
	sudo traceroute  $tracert_pro  $gateway
fi

if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	sudo traceroute  $tracert_pro  $host_ip
fi

echo "step3：查看远程主机TCP/UDP的端口情况"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
fi
