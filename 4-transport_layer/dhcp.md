# dynamic host control protocol

## what is dhcp
dynamic host control protocol，动态主机协议，简单理解，主要作用是对接入的设备
的IP地址进行统一管理，

## how dhcp works
The DHCP employs a connectionless service model, using the User Datagram Protocol (UDP).   
It is implemented with two UDP port numbers for its operations which are the same as for the bootstrap   
protocol (BOOTP). UDP port number 67 is the destination port of a server, and UDP port number 68 is   
used by the client.  
  
DHCP使用udp协议，指定端口，服务端67，客户端68  
  
DHCP operations fall into four phases: server discovery, IP lease offer, IP lease request, and IP lease   
acknowledgement. These stages are often abbreviated as DORA for discovery, offer, request, and acknowledgement.  
  
DHCP协议主要分4个步骤，发现，提供，请求，应答。  
  
The DHCP operation begins with clients broadcasting a request. If the client and server are on different   
subnets, a DHCP Helper or DHCP Relay Agent may be used. Clients requesting renewal of an existing   
lease may communicate directly via UDP unicast, since the client already has an established IP address   
at that point. Additionally, there is a BROADCAST flag (1 bit in 2 byte flags field, where all other bits are  
reserved and so are set to 0) the client can use to indicate in which way (broadcast or unicast) it   
can receive the DHCPOFFER: 0x8000 for broadcast, 0x0000 for unicast.[5] Usually, the DHCPOFFER is sent   
through unicast. For those hosts which cannot accept unicast packets before IP addresses are configured,   
this flag can be used to work around this issue.  
  
首先客户端发送一个广播请求，如果客户端和服务端在不同的子网，则需要DHCP Helper和DHCP Relay Agent。  
客户端已经获取了ip地址，在更新一个ip的租期时，可能直接使用UDP单播。  
  
client   ---discovery--broadcasting-->      server   
client   <--offer------unicast/broadcast--  server  
client   ---request----broadcast----->      server  
client   <--acknowledgement----------       server  

在dhcp协议的字段中，包含一些可选的字段，用于dhcp server向client发送网关，子网掩码，dns等信息。  

## troubleshooting
当主机请求dhcp失败时，通常会被分配一个169.254.x.x的ip地址。  
