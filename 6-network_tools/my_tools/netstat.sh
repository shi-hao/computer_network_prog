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

echo "--------------------------------------------------------------------"
echo -e "\033[31m 配置文件信息：\033[0m"
echo -e "\033[32m 
		目标主机ip：$host_ip  
		目标主机网关：$gateway 

		目标主机traceroute协议：$tracert_pro 

		目标主机TCP端口：$nmap_tcp_port 
		目标主机UDP端口：$nmap_udp_port 
        \033[0m"

pause

echo "--------------------------------------------------------------------"
echo -e "\033[31m step1：查看本地网卡和路由配置\033[0m"

#ifconfig $local_card 
ifconfig
route -n

pause

echo "--------------------------------------------------------------------"
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

echo "--------------------------------------------------------------------"
echo -e "\033[31m step3：目标主机端口测试\033[0m"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
fi

echo "--------------------------------------------------------------------"
echo -e "\033[31m step4：抓包查看协议数据测试\033[0m"
