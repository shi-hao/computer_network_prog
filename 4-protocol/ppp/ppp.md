# PPP(point to point protocol)  
PPP协议是数据链路层协议的一种。  
PPP协议数据帧中有标志数据包开始或者结束的字段，这是链路层协议的重要特点。    
  
PPP frames are variants of HDLC frames:  
<pre>  
-----------------------------------------------------------------------------------      
|Name                   Number of bytes         Description  
-----------------------------------------------------------------------------------      
|Flag                   1                       0x7E, the beginning of a PPP frame  
|Address                1                       0xFF, standard broadcast address  
|Control                1                       0x03, unnumbered data  
|Protocol               2                       PPP ID of embedded data  
|Information            variable (0 or more)    datagram  
|Padding                variable (0 or more)    optional padding  
|Frame Check Sequence   2                       frame checksum  
|Flag                   1                       0x7E, omitted for successive PPP packets  
-----------------------------------------------------------------------------------      
</pre>  
  
