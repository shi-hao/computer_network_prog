#!/bin/bash

# ctrl-c exit
trap "echo 'break and exit'; exit 2" INT

# save log file path
path=./log/

# file name
timestamp=$(date +'%Y-%m-%d-%H:%M:%S')
file_name='iperf_'$timestamp'.log'
echo "file name : $file_name"

# full name
full_name=$path$file_name

# iperf serber ip
svr_ip='192.168.10.3'

# main loop
while true
do 
	sleep 5s
	timestamp=$(date +'%Y-%m-%d-%H:%M:%S')
	echo "time : $timestamp"  >> $full_name
	iperf -c $svr_ip -t 1000 -i 10 >> $full_name
done
