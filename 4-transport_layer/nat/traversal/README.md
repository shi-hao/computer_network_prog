# nat类型  
  
## full cone nat  
  
## restricted cone nat  
  
## restricted port cone nat  
  
## symmetric nat  
  
udp hole punching is possible except the symmetric nat!!    
  
# internet peer to peer communication  
  
  
# UDP NAT穿越的本质？  
UDP client先和处在公网上的server建立通信，server可以知道client的NAT后的IP地址  
和端口号，server将NAT后的IP地址和端口后发送给client，client就可以利用这个IP和  
端口号直接进行通信。  
  
TCP在通信之前要进行三步握手，TCP sever将NAT后的IP地址和端口号发送给client后，  
client无法直接向NAT后的IP和端口号发送数据，TCP实现穿越要比UDP复杂一些，但是可
以实现。  
