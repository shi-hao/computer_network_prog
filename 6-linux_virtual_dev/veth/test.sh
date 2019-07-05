#!/bin/bash

#add veth device
sudo ip link add veth0 type veth peer name veth1

#config ip
sudo ip addr add 192.168.2.11/24   dev veth0

#start the veth device 
sudo ip link set veth0 up  
sudo ip link set veth1 up


#config ip
sudo ip addr add 192.168.2.1/24  dev veth1

