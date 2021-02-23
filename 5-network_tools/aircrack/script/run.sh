#!/bin/bash

#To determine the driver (and the correct procedure to follow)
airmon-ng

#Step 1b - Setting up madwifi-ng
airmon-ng stop wlxec3dfde15940
sudo airmon-ng start wlxec3dfde15940 9

#Step 2 - Start airodump-ng to collect authentication handshake
#Where:
#	-c 9 is the channel for the wireless network
#	--bssid 00:14:6C:7E:40:80 is the access point MAC address. This eliminates
#	extraneous traffic.
#	-w psk is the file name prefix for the file which will contain the IVs.
#	ath0 is the interface name.
sudo airodump-ng -c 9 --bssid 3c:37:86:8a:b3:90 -w psk mon0



