#!/bin/bash 

# import shell script 
source ./my_function.sh

# chose the config file ???
cnf_file_pattern=.cnf
path=/home/bleach/myfile/
all_cnf_files=$(ls -p  $path |	grep -v / | grep "$cnf_file_pattern$")

files_arr=($all_cnf_files)
len=$((${#files_arr[*]}-1))

if [ $len -ge  0 ]; then
	my_echo "red" " find $[len+1] config file"
else 
	my_echo "red" " find config file failed, exit \n  config pattern $cnf_file_pattern, \n  config path is $path"
	exit
fi

my_printf "green" "null" "ID" "file"
for((i=0;i<=len;i++));
do
	my_printf "null" "null" $i ${files_arr[i]}
done 

# Chosing config files
my_echo "red" " please inpute 0~$len to chose the config file"
read num 
if (( $num > $len )) || (( $num < 0 ));then
	my_echo "red" " inpute error, exit!"
	exit
fi

# target file
target_file=${files_arr[$num]}
my_echo "red" " chosing file : $target_file" 

while read line
do  
eval "$line"  
done < $path$target_file 

my_echo "red"   "--------------------------------------------------------------------"
my_echo "null" "\t description：$about_info

\t target ip：$host_ip
\t target gw：$gateway

\t traceroute protocol：$tracert_pro 

\t target tcp port：$nmap_tcp_port 
\t target udp port：$nmap_udp_port"

pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step1：查看本地网卡和路由配置"

#ifconfig $local_card 
ifconfig
my_echo "red" "\n-----this is dividers-----\n"
route -n

pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step2：网络连通测试"
if [ -n "$gateway" ];
then
	ping  -c 5 $gateway
	my_echo "red" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro  $gateway
fi

if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	my_echo "red" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro  $host_ip
fi

pause

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step3：目标主机端口测试"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS -p $nmap_tcp_port  $host_ip
	my_echo "red" "\n-----this is dividers-----\n"
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU -p $nmap_udp_port  $host_ip
	my_echo "red" "\n-----this is dividers-----\n"
fi

my_echo "red" "--------------------------------------------------------------------"
my_echo "red" " step4：抓包查看协议数据测试"
