# PPP(point to point protocol)     
  
## 1.What is PPP and used for?   
PPP:point to point protocol   
PPP协议是数据链路层协议的一种。     
  
Point - to - Point Protocol (PPP) is a communication protocol of the data link   
layer that is used to transmit multiprotocol data between two directly   
connected (point-to-point) computers. It is a byte - oriented protocol that is   
widely used in broadband communications having heavy loads and high speeds.   
Since it is a data link layer protocol, data is transmitted in frames. It is   
also known as RFC 1661   
  
## 2.Packet   
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
  
## 3.Sequence   
  
认证方式    
**Password Authentication Protocol(PAP)**    
PAP authentication is only done at the time of the initial link establishment,    
and verifies the identity of the client using a two-way handshake.    
(1)Client sends username and password. This is sent repeatedly until a response    
   is received from the server.    
(2)Server sends authentication-ack (if credentials are OK) or authentication-nak    
  
**Challenge Handshake Authentication Protocol(CHAP)**    
CHAP is an authentication scheme used by Point-to-Point Protocol (PPP) servers  
to validate the identity of remote clients. CHAP periodically verifies the  
identity of the client by using a three-way handshake. This happens at the  
time of establishing the initial link (LCP), and may happen again at any time  
afterwards. The verification is based on a shared secret (such as the client's  
password).  
  
## 4.Application   
运营商APN理解？   
