#!/bin/bash

# aircrack-ng : 802.11 WEP and WPA/WPA2-PSK key cracking program.

# Try all the passwords in wordlist file:
# aircrack-ng  -w  [wordlist]  [handshake file]
#	-w 密码本文件
#	[handshake file] 握手数据包文件，使用airodump-ng抓取
sudo aircrack-ng -w ./wordlist.txt  ./files/psk-01.cap

