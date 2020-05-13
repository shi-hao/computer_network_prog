# 以太网协议  
数据链路层的核心协议是以太网协议。  

## 以太网协议帧格式      
以太网帧主要包含4部分，18字节。        
<pre>      
--------------------------------------------------------------      
| Des MAC addr | Src MAC addr| Type     |   Payload  | FCS  |      
| 6bytes       | 6 bytes     | 2 bytes  |46-1500bytes|4bytes|      
--------------------------------------------------------------      
</pre>      
Des MAC addr : 目的MAC地址
Src MAC addr : 源MAC地址
Type : Payload字段的协议类型编码      
FCS : frame checke sequence(32-bit CRC)，32比特CRC校验码。      
  
问：以太网协议报文中并没有frame长度的信息，那如何去判断一个frame的长度呢？    
答：frame中虽然没有长度信息，但是物理层有标识长度的机制，以太网依赖于物理层去
	区分两个frame数据包。    
  
问：以太网报文的最大/最小长度？    
答：以太网报文的Payload最大长度为1500，即MTU为1500bytes，以太网报文的最大长度
    是1500+18=1518bytes。最小的Payload长度是46字节，当实际的长度不足46字节时，
	会增补全0数据到46字节，所以最小的字节长度是46+18=64bytes。

## MAC address    
以太网协议的核心字段是MAC地址。      
    
**MAC**    
**单播/组播/广播**    

MAC地址，又称为物理地址(physical address)，长度固定，6个字节，MAC地址也分为三种，    
单播，组播，广播地址。          
        
## 单播(unicast)/组播(multicast)/广播(broadcast)          
1.单播地址  
就是对应网卡的实际物理地址，根据IP包的目的IP地址，查询arp表获取，或者是网关的        
MAC地址。网卡的物理地址的第一个字节的最低位必须是0！！          
        
2.组播地址       
组播MAC地址的第一个字节的最低位必须是1，比如如下都是组播地址。          
0x01-0xff-0xff-0xff-0xff-0xff          
0x33-0x00-0x00-0x00-0x00-0x00          
        
3.广播地址  
广播的MAC地址很固定，是全1，即：          
0xff-0xff-0xff-0xff-0xff-0xff          


## Q&A
MAC地址冲突？MAC地址漂移？如何解决？
