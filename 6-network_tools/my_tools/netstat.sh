#!/bin/bash 

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
if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	traceroute  $tracert_pro  $host_ip
fi
