组播实验  
网络拓扑结构如下  
  
<pre>
----------------------------------------------------------  
              无线无线路由器  
----------------------------------------------------------  
 ||                     ||             ||  
 |PC1|                  |PC2|          |PC3|  
 192.168.3.5            192.168.3.4    192.168.3.3  
 udp_mulitcast_sender   receiver       receiver  
 239.1.1.88:7838  
</pre>
  
 三台PC1,PC2,PC3通过无线wifi连接到路由器,PC1向组播地址239.1.1.88:7838发送组播数据。  
 PC2,PC3可以正常接收到数据。  
  
 使用wireshark抓包发现，三台PC使用的是IGMPv3协议，receiver在启动时，会向广播地址224.0.0.22发送  
 Membership Report数据包。  
  
 本目录的doc文件夹下，有几个很实用的文档，介绍了igmp协议，multicast等知识。  
