# Simple Service Discovery Protocol      
The Simple Service Discovery Protocol (SSDP) is a network protocol based on      
the Internet protocol suite for advertisement and discovery of network      
services and presence information. It accomplishes this without assistance of      
server-based configuration mechanisms, such as Dynamic Host Configuration      
Protocol (DHCP) or Domain Name System (DNS), and without special static      
configuration of a network host. SSDP is the basis of the discovery protocol      
of Universal Plug and Play (UPnP) and is intended for use in residential or      
small office environments. It was formally described in an Internet      
Engineering Task Force (IETF) Internet Draft by Microsoft and Hewlett-Packard      
in 1999. Although the IETF proposal has since expired (April, 2000),[1] SSDP      
was incorporated into the UPnP protocol stack, and a description of the final      
implementation is included in UPnP standards documents.[2][3]      
      
SSDP is a text-based protocol based on HTTP. It uses UDP as the underlying      
transport protocol. Services are announced by the hosting system with      
multicast addressing to a specifically designated IP multicast address at UDP      
port number 1900. In IPv4, the multicast address is 239.255.255.250[4] and      
SSDP over IPv6 uses the address set ff0X::c for all scope ranges indicated by      
X.[5]      
    
This results in the following well-known practical multicast addresses for    
SSDP:    
    
239.255.255.250 (IPv4 site-local address)    
    [FF02::C] (IPv6 link-local)    
    [FF05::C] (IPv6 site-local)    
    [FF08::C] (IPv6 organization-local)    
    [FF0E::C] (IPv6 global)    
    
Additionally, applications may use the source-specific multicast addresses    
derived from the local IPv6 routing prefix, with group ID C (decimal 12).    
    
SSDP uses the HTTP method NOTIFY to announce the establishment or    
withdrawal of services (presence) information to the multicast group. A    
client that wishes to discover available services on a network, uses    
method M-SEARCH. Responses to such search requests are sent via unicast    
addressing to the originating address and port number of the multicast    
request.    
    
Microsoft's IPv6 SSDP implementations in Windows Media Player and Server    
use the link-local scope address. Microsoft uses port number 2869 for    
event notification and event subscriptions. However, early implementations    
of SSDP also used port 5000 for this service.[6]     
  
网络内的主机通过SSDP协议发现网络内服务，SSDP协议使用http协议，UDP组播方式在局  
域网内发送请求，即发送SSDP的M-SEARCH数据包，网域内的主机通过SSDP的NOTIFY数据包  
应答。  
  
SSDP:M-SEARCH Request     UDP:Multicast  
SSDP:NOTIFY   Responses   UDP:Unicast  
