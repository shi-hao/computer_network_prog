# config the local network card interface  
  
## ifconfig  
(1)查看网卡信息：  
ifconfig  
ifconfig	-a  查看所有网卡  
ifconfig	[interface]  查看指定网卡信息  
  
(2)打开/关闭网卡：  
ifconfig [interface]  up/down  
  
ifconfig enp0s31f6 down  
ifconfig enp0s31f6 up  
  
(3)设置网卡ip及其掩码：  
ifconfig [interface] [ip] netmask [mask]  
  
ifconfig enp0s31f6 11.15.244.64 netmask 255.255.255.0  
  
## iwconfig  
(1)查看无线网卡信息：  
iwconfig  
iwconfig  [interface]  
  
(2)设置无线网卡模式/频道/ESSID/密码  
sudo  iwconfig  wlp4s0  mode  ad-hoc  
sudo  iwconfig  wlp4s0  channel  auto  
sudo  iwconfig  wlp4s0  essid  wifi_name  
sudo  iwconfig  wlp4s0  key  1234567890  
