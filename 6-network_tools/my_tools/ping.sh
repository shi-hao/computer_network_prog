#!/bin/bash 

# Trap ctrl-c
trap 'echo "exit ping"; exit' INT

source ./my_function.sh

# Config file
cnf_file=/home/bleach/myfile/ip_host.txt

# Read ip
while read line
do 
	arr=($line)

	# If contain # then break
	if [[ ${arr[0]} =~ "#"  ]] 
	then 
		break
	fi 

	ip_array+=(${arr[0]})
	msg+=(${arr[1]})
done <$cnf_file
len=$((${#ip_array[*]}-1))

# Echo all ip
for((i=0;i<=len;i++));
do
	echo -e "[$i] \t ${ip_array[i]} \t  ${msg[i]}"
done 

# Ping all ip
sleep_s=$1  #interval
while true 
do
	for((i=0;i<=len;i++));
	do
		outstr=$(ping -c 1 ${ip_array[i]})
		if [ $? -eq 0 ]; then
			echo "------------------------------------------------"
			my_echo "blue"  "$outstr"
			my_echo "green" "${msg[i]}--${ip_array[i]} alive"
			sleep $sleep_s
		else
			echo "------------------------------------------------"
			my_echo "blue" "$outstr"
			my_echo "red"  "${msg[i]}--${ip_array[i]} ping faild"
			echo -e "\a" #alarm 
		fi
	done 
done
