# L2TP(Layer 2 Tunneling Protocol)  
L2TP数据包通过UDP协议传输，因为L2TP不能提供很强的安全性，所以经常使用IPsec来保证L2TP数据的安全。    
  
L2TP normally uses TCP port 1701, but when it’s paired up with IPSec it also  
uses UDP ports 500 (for IKE – Internet Key Exchange), 4500 (for NAT), and 1701  
(for L2TP traffic).  
