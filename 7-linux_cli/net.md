# wireless command  
## ifconfig  

1. print all net card info  
ifconfig -a  

2. set the net card ip  
ifconfig [interface] [ip] netmask  [mask]  [dev]  

3. on/off the card  
ifconfig [interface] down  
ifconfig [interface] up  


## iwconfig  
similar to ifconfig, interface wireless config  

1. print wireless card info  
iwconfig [interface]  

2. set the wireless card mode key essid channel  
sudo iwconfig wlp4s0 mode ad-hoc  
sudo iwconfig wlp4s0 channel auto  
sudo iwconfig wlp4s0 essid 'mywifi'  
sudo iwconfig wlp4s0 key 1234567890  
