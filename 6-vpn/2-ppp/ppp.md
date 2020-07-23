# PPP(point to point protocol)     
  
## 1.What is PPP and used for?   
PPP:point to point protocol   

  
## 2.Packet   
<pre>     
-----------------------------------------------------------------------------------         
|Name                   Number of bytes         Description     
-----------------------------------------------------------------------------------         
|Flag                   1                       0x7E, the beginning of a PPP frame     
|Address                1                       0xFF, standard broadcast address     
|Control                1                       0x03, unnumbered data     
|Protocol               2                       identifies the protocol encapsulated in Information field     
|Information            variable (0 or more)    datagram     
|Padding                variable (0 or more)    optional padding     
|Frame Check Sequence   2                       frame checksum     
|Flag                   1                       0x7E, omitted for successive PPP packets     
-----------------------------------------------------------------------------------         

Protocol field:
value (in hex) Protocol Name
0001 to 001f   reserved (transparency inefficient)
0021           Internet Protocol
0023           OSI Network Layer

c021           Link Control Protocol
c023           Password Authentication Protocol
c223           Challenge Handshake Authentication Protocol
</pre>     
  
## 3.Sequence   

(1)Each end of the PPP link must first send LCP packets to configure and test the data link.
(2)After the link has been established, the peer may be authenticated.
(3)Then, PPP must send NCP packets to choose and configure one or more network-layer protocols.

<pre>
Phase Diagram

-----------           --------------                 --------             ----------
|establish|--opened-->|authenticated|--sucess/none-->|network|--closing-->|terminate|
-----------           --------------                 --------             ----------
     |--fail-------------->|--fail---------------------------------------------/\

Link Establishment Phase
The Link Control Protocol (LCP) is used to establish the connection through an exchange of Configure packets. 

Authentication Phase
By default, authentication is not necessary.

Network-Layer Protocol Phase
Once PPP has finished the previous phases, each network-layer protocol (such
as IP) MUST be separately configured by the appropriate Network Control Protocol (NCP).
</pre>
  
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
