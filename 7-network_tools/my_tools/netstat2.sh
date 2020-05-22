#!/bin/bash 

# Import shell script 
source ./my_function.sh

# Trap ctrl-c
my_break

# Get all the config files 
cnf_file_pattern=.cnf
path=/home/bleach/myfile/
all_cnf_files=$(ls -p  $path |	grep -v / | grep "$cnf_file_pattern$")

files_arr=($all_cnf_files)
len=$((${#files_arr[*]}-1))

if [ $len -ge  0 ]; then
	my_echo "blue" " find $[len+1] config file"
else 
	my_echo "blue" " find config file failed, exit \n config pattern $cnf_file_pattern, \n config path is $path"
	exit
fi

my_printf "null" "null" "ID" "file"
for((i=0;i<=len;i++));
do
	my_printf "null" "null" $i ${files_arr[i]}
done 

# Choosing config files
in_id=""
while [[ ! "$in_id" =~ ^[0-9]+$ || $in_id -gt $len || $in_id -lt 0 ]]; do
	my_echo "blue" " please input 0~$len to choose the config file"
	read in_id
done

# Target file
target_file=${files_arr[$in_id]}
my_echo "blue" " choosing file : $target_file" 

while read line
do  
eval "$line"  
done < $path$target_file 

my_echo "blue"   "--------------------------------------------------------------------"
my_echo "null" "\t description        ：$about_info
\t target ip          ：$host_ip
\t target gw          ：$gateway
\t traceroute protocol：$tracert_pro 
\t nmap block ping    : $nmap_block_ping 
\t nmap tcp port      ：$nmap_tcp_port 
\t nmap udp port      ：$nmap_udp_port
\t ntp domain         ：$ntp_domain"

my_pause

my_echo "blue" "--------------------------------------------------------------------"
my_echo "blue" " step1：Searching the local route table"
if [ -n "$gateway" ];
then
	ip route list match $gateway
	if [ $? -ne 0 ]; then
		my_echo "red" "\nGateway $gateway route table match failed\n"
		route -n
	fi
fi

if [ -n "$host_ip" ];
then
	ip route list match $host_ip
	if [ $? -ne 0 ]; then
		my_echo "red" "\nHost $host_ip route table match failed\n"
		route -n
	fi
fi

my_pause

my_echo "blue" "--------------------------------------------------------------------"
my_echo "blue" " step2：Searching the local ARP table"
if [ -n "$gateway" ];
then
	#out=eval ip neighbor show $host_ip
	out=$(ip neighbor show $host_ip)
	echo $out
	if [ -z "$out" ]; then
		my_echo "red" "\nGateway $gateway ARP table match failed\n"
		arp -n
	fi
fi

if [ -n "$host_ip" ];
then
	#out=eval ip neighbor show $host_ip
	out=$(ip neighbor show $host_ip)
	echo $out
	if [ -z "$out" ]; then
		my_echo "red" "\nHost $host_ip ARP table match failed\n"
		arp -n
	fi
fi

my_pause

my_echo "blue" "--------------------------------------------------------------------"
my_echo "blue" " step3：Net connectivity test"
if [ -n "$gateway" ];
then
	ping  -c 5 $gateway
	my_echo "blue" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro -n $gateway
fi

if [ -n "$host_ip" ];
then
	ping  -c 5 $host_ip
	my_echo "blue" "\n-----this is dividers-----\n"
	sudo traceroute  $tracert_pro -n $host_ip
fi

my_pause

my_echo "blue" "--------------------------------------------------------------------"
my_echo "blue" " step4：Target host port connectivity test"

if [ -n "$nmap_tcp_port" ];
then
	sudo nmap -sS $nmap_block_ping -p $nmap_tcp_port  $host_ip
fi

if [ -n "$nmap_udp_port" ];
then
	sudo nmap -sU $nmap_block_ping -p $nmap_udp_port  $host_ip
fi

my_echo "blue" "--------------------------------------------------------------------"
my_echo "blue" " step5：Catch the data using WireShark or tcpdump"


if [ -n "$ntp_domain" ];
then
	my_echo "blue" "--------------------------------------------------------------------"
	my_echo "blue" " ntp同步时间测试"
	ntpdate -q $ntp_domain
fi
