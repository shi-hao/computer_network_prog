#!/bin/bash

# airmon-ng : 用于改变网卡的工作模式 

# airmon-ng check : 检测系统中影响aircrack运行的进程
# airmon-ng check kill ： 杀掉影响aircrack运行的进程
sudo airmon-ng check kill

# airmon-ng start [nic] : 设置网卡为monitor模式 
# airmon-ng stop [nic] ： 关闭网卡monitor模式
sudo airmon-ng stop wlp4s0
sleep 5
sudo airmon-ng start wlp4s0
