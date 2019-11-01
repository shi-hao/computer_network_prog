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
		目标主机ip：$host_ip  
		目标主机网关：$gateway 

		目标主机traceroute协议：$tracert_pro 

		目标主机TCP端口：$nmap_tcp_port 
		目标主机UDP端口：$nmap_udp_port 
        \033[0m"
echo "--------------------------------------------"

# Get all interfaces
all_inter=$(ls /sys/class/net)
inter_arr=($all_inter)
len=$((${#inter_arr[*]}-1))

# Echo all interfaces
printf "\033[31m%-5s  %-20s\n\033[0m" "ID" "Interface"
for((i=0;i<=len;i++));
do
	printf "\033[4m%-5s  %-20s\n\033[0m" $i ${inter_arr[i]}
done 

# Chosing interface
echo -e "\033[31m please inpute 0~$len to chose the interface\033[0m"
read num 

# Interface
local_card=${inter_arr[$num]}
echo -e "\033[31m interface:$local_card \033[0m"


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
