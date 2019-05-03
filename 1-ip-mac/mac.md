#MAC(media access control address)
mac地址，又称为物理地址(pyhsical address)，长度固定，6个字节，mac地址也分为三种，  
单播，组播，广播地址。  

##单播(unicast)
单播地址，就是对应网卡的实际物理地址，根据ip包的目的ip地址，查询arp表获取，或者是网关  
的mac地址。  
网卡的物理地址的第一个字节的最低位必须是0！！  

##组播(multicast)
组播mac地址的第一个字节的最低位必须是1，比如如下都是组播地址。  
0x01-0xff-0xff-0xff-0xff-0xff  
0x33-0x00-0x00-0x00-0x00-0x00  


##广播(broadcast)
广播的mac地址很固定，是全1，即：  
0xff-0xff-0xff-0xff-0xff-0xff  

