#!/bin/bash 

#config the interface ip using cmd
sudo ifconfig enp0s31f6 down
sudo ifconfig enp0s31f6 11.15.244.63 netmask 255.255.255.0 
sudo route add default gw 11.15.244.254
sudo ifconfig enp0s31f6 up

