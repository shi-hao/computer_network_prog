#!/bin/bash

trap "echo 'break and exit'; exit 2" INT

timestamp=$(date +'%Y-%m-%d-%H:%M:%S')
file_name='iperf_'$timestamp'.log'
echo "file name : $file_name"
svr_ip='192.168.10.3'

while true
do 
	sleep 5s
	timestamp=$(date +'%Y-%m-%d-%H:%M:%S')
	echo "time : $timestamp"  >> ./log/$file_name
	iperf -c $svr_ip -t 1000 -i 10 >> ./log/$file_name
done
