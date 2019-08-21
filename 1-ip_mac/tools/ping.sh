#!/bin/bash 

# Trap ctrl-c
trap 'echo "exit ping"; exit' INT

# Config file
cnf_file=/home/bleach/myfile/ip_host.txt

# Read ip
OLD_IFS=$IFS
IFS=" "
while read line
do 
	arr=($line)
	ip_array+=(${arr[0]})
	msg+=(${arr[1]})
done <$cnf_file
IFS=$OLD_IFS
len=$((${#ip_array[*]}-1))

# Echo all ip
for((i=0;i<=len;i++));
do
	echo -en "[$i] \t ${ip_array[i]} \t  ${msg[i]} \n"
done 

# Ping all ip
sleep_s=$1  #间隔时间
while true 
do
	for((i=0;i<=len;i++));
	do
		outstr=$(ping -c 1 ${ip_array[i]})
		if [ $? -eq 1 ]; then
			echo "------------------------------------------------"
			echo -e "\033[31m $outstr \033[0m"
			echo -e "\033[31m ${msg[i]}--${ip_array[i]} ping faild \033[0m"
			echo -e "\a" #alarm 
		else
			echo "------------------------------------------------"
			echo $outstr
			echo -e "\033[32m ${msg[i]}--${ip_array[i]} alive \033[0m"
			sleep $sleep_s
		fi
	done 
done
