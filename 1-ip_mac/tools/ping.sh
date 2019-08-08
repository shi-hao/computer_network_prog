#!/bin/bash 

#trap ctrl-c
trap 'echo "INTERRUPTED!"; exit' INT

# Read ip
OLD_IFS=$IFS
IFS=" "
while read line
do 
	arr=($line)
	ip_array+=(${arr[0]})
	msg+=(${arr[1]})
done <./ip_host.txt
IFS=$OLD_IFS
len=$((${#ip_array[*]}-1))

# Echo all ip
for((i=0;i<=len;i++));
do
	echo -en "[$i] \t ${ip_array[i]} \t  ${msg[i]} \n"
done 

# Ping all ip
while true 
do
	for((i=0;i<=len;i++));
		do
			ping -c 1 ${ip_array[i]} 
			if [ $? -eq 1 ]; then
				echo -e "\033[31m ${msg[i]} ping faild\033[0m"
				echo -e "\a" #alarm 
			else
				sleep 4
			fi
		done 
done
