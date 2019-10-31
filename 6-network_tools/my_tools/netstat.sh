#!/bin/bash 

#pause function
pause(){
	while true
	do
		isContinue='y'
		read -p '请输入y继续，输入n退出 [y/n]' isContinue
		if [ "$isContinue" == "y" ]; then
			break
		elif [ "$isContinue" == "n" ]; then
			exit
		fi
	done
}

while read line
do  
eval "$line"  
done < des_ip.txt  

echo "--------------------------------------------"
echo -e "\033[32m 
		本地网卡：$local_card 

		目标主机ip：$host_ip  
		目标主机网关：$gateway 

		目标主机traceroute协议：$tracert_pro 

		目标主机TCP端口：$nmap_tcp_port 
		目标主机UDP端口：$nmap_udp_port 
        \033[0m"
echo "--------------------------------------------"

pause

echo -e "\033[31m step1：查看本地网卡和路由配置\033[0m"

ifconfig $local_card 
route -n

pause

echo -e "\033[31m step2：网络连通测试\033[0m"
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

pause

echo -e "\033[31m step3：目标主机端口测试\033[0m"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
fi
