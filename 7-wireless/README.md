# linux wireless command    
## ifconfig    
  
1. print all net card info    
ifconfig  -a    
  
2. set the net card ip    
ifconfig  [interface]  [ip]  netmask [mask]      
ifconfig  eht0 192.168.10.10 netmask 255.255.255.0    
  
3. on/off the card    
ifconfig  [interface]  down    
ifconfig  [interface]  up    
  
  
## iwconfig    
similar to ifconfig, interface wireless config    
  
1. print wireless card info    
iwconfig  [interface]    
  
2. set the wireless card mode key essid channel    
sudo  iwconfig  wlp4s0  mode  ad-hoc    
sudo  iwconfig  wlp4s0  channel  auto    
sudo  iwconfig  wlp4s0  essid  wifi_name     
sudo  iwconfig  wlp4s0  key  1234567890    
  
  
## linux wifi working mode  
1. AccessPoint infrastructure mode(master mode)    
An Access Point acts as the Master device in a managed wireless network.    
具体到某些无线设备，ap模式下，可以工作在网桥模式下，或者路由模式，网桥模式相当于    
一个无线接入的交换机，路由模式相当于一个网关，有对上的路由功能。    
  
2. Station infrastructure mode(managed mode or client mode)    
wifi常用模式，用于接入ap，进行组网。    
  
3. monitor mode    
此模式下，无线网卡可以接收监测所有的网络数据包。    
  
4. ad-hoc(IBSS)    
wifi peer-to-peer mode, 用于设备之间直连传输。    
  
5. repeater(wireless distribution system (WDS))  
中继模式，扩大无线网络覆盖范围。    
  
6. mesh  
  
7. wifi direct  
wifi peer-to-peer mode.  
  
8. Tunneled Direct Link Setup(TDLS)  
  
  
## linux wifi typical network   
<img src="https://github.com/shi-hao/computer_network_prog/blob/master/7-wireless/wifi_app_mode.jpg" width    ="606" height="886" />  
