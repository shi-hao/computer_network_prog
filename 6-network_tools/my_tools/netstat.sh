#!/bin/bash 

# import base.sh
source ./base.sh

# chose the config file ???
cnf_file_pattern=.cnf
path=/home/bleach/myfile/
all_cnf_files=$(ls -p  $path |	grep -v / | grep "$cnf_file_pattern$")

files_arr=($all_cnf_files)
len=$((${#files_arr[*]}-1))

if [ $len -ge  0 ]; then
	echo_red " find $[len+1] config file\n"
else 
	echo_red " find config file failed, exit \n  config pattern $cnf_file_pattern, \n  config path is $path"
	exit
fi

printf_2_yell "ID" "file"
for((i=0;i<=len;i++));
do
	printf_2_default $i ${files_arr[i]}
done 

# Chosing config files
echo_red " please inpute 0~$len to chose the config file"
read num 

# target file
target_file=${files_arr[$num]}
echo -e " chosing file : $target_file" 

while read line
do  
eval "$line"  
done < $path$target_file 

echo_red "--------------------------------------------------------------------"
echo_green " 配置文件信息："
echo_green "
		说明信息：$about_info		

		目标主机ip：$host_ip  
		目标主机网关：$gateway 

		目标主机traceroute协议：$tracert_pro 

		目标主机TCP端口：$nmap_tcp_port 
		目标主机UDP端口：$nmap_udp_port"

pause

echo_red "--------------------------------------------------------------------"
echo_red " step1：查看本地网卡和路由配置"

#ifconfig $local_card 
ifconfig
echo -e "\n=================================\n"
route -n

pause

echo_red "--------------------------------------------------------------------"
echo_red " step2：网络连通测试"
if [ -n "$gateway" ];
then
	ping  -c 5 $gateway
	echo -e "\n=================================\n"
	sudo traceroute  $tracert_pro  $gateway
fi

if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	echo -e "\n=================================\n"
	sudo traceroute  $tracert_pro  $host_ip
fi

pause

echo_red "--------------------------------------------------------------------"
echo_red " step3：目标主机端口测试"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
	echo -e "\n=================================\n"
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
	echo -e "\n=================================\n"
fi

echo_red "--------------------------------------------------------------------"
echo_red " step4：抓包查看协议数据测试"
