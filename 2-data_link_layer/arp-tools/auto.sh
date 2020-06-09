#sudo ./arpspoof.elf -i eno1 -t 192.168.0.1 -s 192.168.0.1
#sudo ./arpspoof.elf -i eno1 -s 192.168.0.1 -t 192.168.0.1 -g p 
#sudo ./arptool.elf -q -i eno1 -Sip 192.168.0.1 -Smac ff:ff:ff:ff:ff:ff -Tip 192.168.0.1 -Tmac ff:ff:ff:ff:ff:ff
sudo ./arptool.elf -q -i eno1 -Sip 192.168.0.1  -Tip 192.168.0.1
