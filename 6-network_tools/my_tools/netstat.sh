#!/bin/bash 

# import shell script 
source ./my_function.sh

# Trap ctrl-c
my_break

# chose the config file ???
cnf_file_pattern=.cnf
path=/home/bleach/myfile/
all_cnf_files=$(ls -p  $path |	grep -v / | grep "$cnf_file_pattern$")

files_arr=($all_cnf_files)
len=$((${#files_arr[*]}-1))

if [ $len -ge  0 ]; then
	my_echo "red" " find $[len+1] config file"
else 
	my_echo "red" " find config file failed, exit \n config pattern $cnf_file_pattern, \n config path is $path"
	exit
fi

my_printf "green" "null" "ID" "file"
for((i=0;i<=len;i++));
do
	my_printf "null" "null" $i ${files_arr[i]}
done 

# Chosing config files
in_id=""
while [[ ! "$in_id" =~ ^[0-9]+$ || $in_id -gt $len || $in_id -lt 0 ]]; do
	my_echo "red" " please input 0~$len to chose the config file"
	read in_id
done

# target file
target_file=${files_arr[$in_id]}
my_echo "red" " chosing file : $target_file" 

while read line
do  
eval "$line"  
done < $path$target_file 

my_echo "red"   "--------------------------------------------------------------------"
my_echo "null" "\t description        ：$about_info
\t target ip          ：$host_ip
\t target gw          ：$gateway
\t traceroute protocol：$tracert_pro 
\t nmap tcp port      ：$nmap_tcp_port 
\t nmap udp port      ：$nmap_udp_port
\t ntp domain         ：$ntp_domain"

my_pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step1：查看本地网卡和路由配置"

#ifconfig $local_card 
ifconfig
my_echo "red" "\n-----this is dividers-----\n"
route -n

my_pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step2：网络连通测试"
if [ -n "$gateway" ];
then
	ping  -c 5 $gateway
	my_echo "red" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro -n $gateway
fi

if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	my_echo "red" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro -n $host_ip
fi

my_pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step3：目标主机端口测试"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
fi

if [ -n "$ntp_domain" ];
then
	my_echo "red" "--------------------------------------------------------------------"
	my_echo "red" " ntp同步时间测试"
	ntpdate -q $ntp_domain
fi

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step4：抓包查看协议数据测试"
