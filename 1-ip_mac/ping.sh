#!/bin/bash 

# Read ip
OLD_IFS=$IFS
IFS=" "
while read line
do 
	arr=($line)
	ip_array+=(${arr[0]})
	msg+=(${arr[3]})
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
		done 
done
