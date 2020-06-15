#ARP REQUEST(广播)
# arp -q -i interface [-Sip arp_src_ip] [-Smac arp_src_mac] -Tip arp_tar_ip
#    -Tip必须设置
#    -Sip和-Smac可选设置，如果不设置，会按照interface的IP地址和MAC地址进行组包。
# 
#ARP REPLY(单播或者广播)
# arp -p -i interface [-Sip arp_src_ip] [-Smac arp_src_mac] -Tip arp_tar_ip [-Tmac arp_tar_mac]
#    -Tip必须设置
#    -Sip和-Smac可选设置，如果不设置，会按照interface的IP地址和MAC地址进行组包。
#    -Tmac可选设置，如果不设置，会查询ARP Table，按照Tip实际的MAC地址进行组包。

# ARP Request
## Normal arp request
## sudo ./arptool.elf -q -i iface -Tip tar_ip
#sudo ./arptool.elf -q -i eno1 -Tip 192.168.0.100

## Gratuitous arp request
## sudo ./arptool.elf -q -i iface -Tip iface_ip
#sudo ./arptool.elf -q -i eno1 -Tip 192.168.0.129

# ARP Reply
## Normal arp reply
## sudo ./arptool.elf -p -i iface  -Tip tar_ip
sudo ./arptool.elf -p -i eno1 -Tip 192.168.0.100

## arp reply cheat
## sudo ./arptool.elf -p -i iface -Sip gw_ip -Tip tar_ip
#sudo ./arptool.elf -p -i eno1 -Sip 192.168.0.1 -Tip 192.168.0.129

## sudo ./arptool.elf -p -i iface -Sip gw_ip -Tip gw_ip -Tmac 00:00:00:00:00:00
#sudo ./arptool.elf -p -i eno1 -Sip 192.168.0.1 -Tip 192.168.0.1 -Tmac 00:00:00:00:00:00
