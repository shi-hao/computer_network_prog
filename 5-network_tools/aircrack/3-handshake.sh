#!/bin/bash

# airodump-ng : Capture raw 802.11 frames. 

# Catch handshake packets
#	airodump-ng -w [文件名] -bssid [AP_MAC] -c [channel_number]  [moniter_nic]
#		-w       保存抓到的握手数据到文件
#		-bssid   ap mac
#		-c       ap channel number

#sudo airodump-ng -w ./files/psk --bssid E4:F4:C6:0C:F7:5D -c 13  wlp4s0mon 
#sudo airodump-ng -w ./files/psk --bssid 40:31:3C:18:6C:EF -c 6  wlp4s0mon 
#sudo airodump-ng -w ./files/psk --bssid 88:C3:97:BC:7B:56 -c 8  wlp4s0mon 
#sudo airodump-ng -w ./files/psk --bssid B4:0F:3B:95:78:28 -c 1  wlp4s0mon 
#sudo airodump-ng -w ./files/psk --bssid  3C:37:86:8A:B3:8F -c 9  mon0 
sudo airodump-ng -w ./files/psk --bssid   5E:66:08:08:E8:C3 -c 6  mon0 
