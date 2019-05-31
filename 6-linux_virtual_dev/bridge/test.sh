#/bin/bash

#create bridge device 
sudo ip link add name br0 type bridge
sudo ip link set br0 up

#create veth device
sudo ip link add veth0 type veth peer name veth1 
sudo ip addr add 192.168.3.101/24 dev veth0
sudo ip addr add 192.168.3.102/24 dev veth1
sudo ip link set veth0 up 
sudo ip link set veth1 up 


#veth0 connect to br0
sudo ip link set dev veth0 master br0
