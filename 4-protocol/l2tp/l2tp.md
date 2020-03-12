# L2TP(Layer 2 Tunneling Protocol)  
L2TP数据包通过UDP协议传输，因为L2TP不能提供很强的安全性，所以经常使用IPsec来保证L2TP数据的安全。    

The entire L2TP packet, including payload and L2TP header, is sent within a
User Datagram Protocol (UDP) datagram.  
  
L2TP normally uses TCP port 1701, but when it’s paired up with IPSec it also  
uses UDP ports 500 (for IKE – Internet Key Exchange), 4500 (for NAT), and 1701  
(for L2TP traffic).  

The two endpoints of an L2TP tunnel are called the LAC (L2TP Access Concentrator) 
and the LNS (L2TP Network Server).

## packet structure
An L2TP packet consists of :
<pre>
-------------------------------------------------
|Bits 0–15                |Bits 16–31
-------------------------------------------------
|Flags and Version Info   |Length (opt)
-------------------------------------------------
|Tunnel ID                |Session ID
-------------------------------------------------
|Ns (opt)                 |Nr (opt)
-------------------------------------------------
|Offset Size (opt)        |Offset Pad (opt)......
-------------------------------------------------
|              Payload data 
-------------------------------------------------
</pre>

## L2TP packet exchange
At the time of setup of L2TP connection, many control packets are exchanged between 
server and client to establish tunnel and session for each direction. One peer requests 
the other peer to assign a specific tunnel and session id through these control packets.
Then using this tunnel and session id, data packets are exchanged with the compressed 
PPP frames as payload.

The list of L2TP Control messages exchanged between LAC and LNS, for handshaking before 
establishing a tunnel and session in voluntary tunneling method are 








## L2TP/IPsec

