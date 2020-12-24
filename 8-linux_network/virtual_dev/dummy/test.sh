#/bin/bash

#create bridge device 
sudo ip link add name mybr0 type bridge
sudo ip link set mybr0 up
sudo ip addr add 192.168.100.1 dev mybr0

#create dummy device
sudo ip link add eth10 type dummy
sudo ip link add eth11 type dummy


#veth0 connect to mybr0
sudo ip link set dev eth10 master mybr0
sudo ip link set dev eth11 master mybr0
