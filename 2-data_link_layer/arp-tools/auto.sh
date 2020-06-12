#send arp request to ip 192.168.0.100
#sudo ./arptool.elf -q -i eno1 -Sip 192.168.0.1  -Tip 192.168.0.100


#send arp reply to 
sudo ./arptool.elf -p -i eno1 -Sip 192.168.0.1
