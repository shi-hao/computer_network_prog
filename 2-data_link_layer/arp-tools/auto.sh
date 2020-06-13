#arp request
#sudo ./arptool.elf -q -i wlp4s0 -Tip 192.168.31.1

#arp reply
sudo ./arptool.elf -p -i wlp4s0  -Tip 192.168.0.120

#arp reply
#sudo ./arptool.elf -p -i wlp4s0  -Tip 192.168.0.120 -Tmac 00:00:00:00:00:00

#arp reply
#sudo ./arptool.elf -p -i wlp4s0  -Tip 192.168.31.1

#arp reply
#sudo ./arptool.elf -p -i wlp4s0  -Sip 192.168.31.1 -Tip 192.168.31.1 -Tmac 00:00:00:00:00:00
