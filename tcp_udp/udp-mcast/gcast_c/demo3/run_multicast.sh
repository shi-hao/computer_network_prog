#!/bin/bash

#if [ command ];then 注意[]前后的空格
if [ "$#" -eq "0" ];then
	echo "please input param: s or r, s=sender r=receiver"
elif [ "$1" = "s" ];then 
#./sender 230.1.1.88 7838 10.8.0.1
	./sender 230.1.1.88 7838
elif [ "$1" = "r" ];then
#./receiver 230.1.1.88 7838 10.8.0.8
	./receiver 230.1.1.88 7838 192.168.0.129
else 
	echo "wrong param!"
fi

