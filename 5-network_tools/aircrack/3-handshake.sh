#!/bin/bash

# Catch handshake packets
#	airodump-ng -w [文件名] -bssid [AP_MAC] -c [channel_number]  [moniter_nic]
#		-w       保存抓到的握手数据到文件
#		-bssid   ap mac
#		-c       ap channel number
sudo airodump-ng -w psk --bssid E4:F4:C6:0C:F7:5D -c 1  mon0 
