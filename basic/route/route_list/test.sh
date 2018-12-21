#!/bin/bash

#./run &
./run &

route -n
ifconfig -a

sudo ifconfig tun0 192.168.11.10
route add -net 192.168.11.0 netmask 255.255.255.0 tun0

route -n
ifconfig -a
