# dynamic host control protocol  
  
## what is DHCP and used for?  
名词解释：DHCP，dynamic host control protocol，动态主机协议  
用    途：主要作用是对接入设备动态分配IP地址，网关，掩码，DNS等网络参数。  
  
<pre>  
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+  
| op (1)        | htype (1)     | hlen (1)      | hops (1)      |  
+---------------+---------------+---------------+---------------+  
| xid (4)                                                       |  
+-------------------------------+-------------------------------+  
| secs (2)                      | flags (2)                     |  
+-------------------------------+-------------------------------+  
| ciaddr (4)                                                    |  
+---------------------------------------------------------------+  
| yiaddr (4)                                                    |  
+---------------------------------------------------------------+  
| siaddr (4)                                                    |  
+---------------------------------------------------------------+  
| giaddr (4)                                                    |  
+---------------------------------------------------------------+  
| chaddr (16)                                                   |  
+---------------------------------------------------------------+  
| sname (64)                                                    |  
+---------------------------------------------------------------+  
| file (128)                                                    |  
+---------------------------------------------------------------+  
| options (variable)                                            |  
+---------------------------------------------------------------+  
  
FIELD   OCTETS    DESCRIPTION  
-----   ------    -----------  
 op       1       Message op code / message type.  
                  1 = BOOTREQUEST, 2 = BOOTREPLY  
  
 htype    1       Hardware address type, see ARP section in "Assigned  
                  Numbers" RFC; e.g., ’1’ = 10mb ethernet.  
  
 hlen     1       Hardware address length (e.g. ’6’ for 10mb ethernet).  
 hops     1       Client sets to zero, optionally used by relay agents  
                  when booting via a relay agent.  
  
 xid      4       Transaction ID, a random number chosen by the  
                  client, used by the client and server to associate  
                  messages and responses between a client and a server.  
  
 secs     2       Filled in by client, seconds elapsed since client  
                  began address acquisition or renewal process.  
  
 flags    2       Flags (see figure 2).  
 ciaddr   4       Client IP address; only filled in if client is in  
                  BOUND, RENEW or REBINDING state and can respond to ARP requests.  
  
 yiaddr   4       ’your’ (client) IP address.  
 siaddr   4       IP address of next server to use in bootstrap;  
                  returned in DHCPOFFER, DHCPACK by server.  
  
 giaddr   4       Relay agent IP address, used in booting via a relay agent.  
 chaddr   16      Client hardware address.  
 sname    64      Optional server host name, null terminated string.  
 file     128     Boot file name, null terminated string; "generic"  
                  name or null in DHCPDISCOVER, fully qualified  
                  directory-path name in DHCPOFFER.  
  
 options  var     Optional parameters field. See the options  
                  documents for a list of defined options.  
</pre>  
  
## how DHCP works?  
DHCP使用UDP协议，指定端口，服务端67，客户端68。   
DHCP协议主要分4个步骤，发现，提供，请求，应答。    
首先客户端发送一个广播请求，如果客户端和服务端在不同的子网，则需要DHCP Helper和DHCP Relay Agent。    
客户端已经获取了IP地址，在更新一个IP的租期时，可能直接使用UDP单播。    
<pre>  
	client   ---discovery--broadcasting-->      server     
	client   <--offer--unicast/broadcast--      server    
	client   ---request----broadcast----->      server    
	client   <--acknowledgement-----------      server    
  
1.DHCP DISCOVER  
--------------------------------------------  
Octet 0     Octet 1     Octet 2     Octet 3  
--------------------------------------------  
OP          HTYPE 	    HLEN 	    HOPS  
0x01        0x01 	    0x06 	    0x00  
--------------------------------------------  
XID  
0x3903F326  
--------------------------------------------  
SECS 	                FLAGS  
0x0000 	                0x0000  
--------------------------------------------  
CIADDR (Client IP address)  
0x00000000  
--------------------------------------------  
YIADDR (Your IP address)  
0x00000000  
--------------------------------------------  
SIADDR (Server IP address)  
0x00000000  
--------------------------------------------  
GIADDR (Gateway IP address)  
0x00000000  
--------------------------------------------  
CHADDR (Client hardware address)  
0x00053C04  
0x8D590000  
0x00000000  
0x00000000  
--------------------------------------------  
192 octets of 0s, or overflow space for additional options; BOOTP legacy.  
--------------------------------------------  
Magic cookie  
0x63825363  
--------------------------------------------  
DHCP options  
0x350101       53(DHCP Message Type)  
               1(len)  
               1(Discover)  
0x3204c0a80164 50(Requested IP)  
               4(len)  
               192.168.1.100(IP)  
0x370401030f06 55 (Parameter Request List)  
               1 (Request Subnet Mask),  
               3 (Router),  
               15 (Domain Name),  
               6 (Domain Name Server)  
0xff 255 (Endmark)   
--------------------------------------------  
  
2.DHCP OFFER   
--------------------------------------------  
Octet 0   Octet 1   Octet 2    Octet 3  
--------------------------------------------  
OP        HTYPE 	HLEN 	   HOPS  
0x02 	  0x01 	    0x06 	   0x00  
--------------------------------------------  
XID  
0x3903F326  
--------------------------------------------  
SECS 	        FLAGS  
0x0000 	        0x0000  
--------------------------------------------  
CIADDR (Client IP address)  
0x00000000  
--------------------------------------------  
YIADDR (Your IP address)  
0xC0A80164 (192.168.1.100)  
--------------------------------------------  
SIADDR (Server IP address)  
0xC0A80101 (192.168.1.1)  
--------------------------------------------  
GIADDR (Gateway IP address)  
0x00000000  
--------------------------------------------  
CHADDR (Client hardware address)  
0x00053C04  
0x8D590000  
0x00000000  
0x00000000  
--------------------------------------------  
192 octets of 0s; BOOTP legacy.  
--------------------------------------------  
Magic cookie  
0x63825363  
--------------------------------------------  
DHCP options  
0x350101               53(DHCP Message Type)  
                       1(len)  
                       2(DHCP Offer)  
0x0104ffffff00         1(subnet mask)  
                       4(len)   
                       255.255.255.0(mask)  
0x0304c0a800013        3(Router)  
                       4(len)  
                       192.168.1.1(router)  
0x330400015130         51(IP address lease time)  
                       4(len)   
                       86320s(time)  
0x3604c0a80001         54(DHCP server)  
                       4(len)  
                       192.168.1.1(server)  
0x0608ca6a0014ca6a2e97 6 (DNS servers)  
                       8(len)  
                       202.106.0.20  
                       202.106.46.152  
--------------------------------------------  
  
3.DHCP REQUEST   
--------------------------------------------  
Octet 0     Octet 1 	Octet 2 	Octet 3  
--------------------------------------------  
OP      	HTYPE 	    HLEN 	    HOPS  
0x01 	    0x01 	    0x06 	    0x00  
--------------------------------------------  
XID  
0x3903F326  
--------------------------------------------  
SECS 	                FLAGS  
0x0000 	0x0000  
--------------------------------------------  
CIADDR (Client IP address)  
0x00000000  
--------------------------------------------  
YIADDR (Your IP address)  
0x00000000  
--------------------------------------------  
SIADDR (Server IP address)  
0xC0A80101 (192.168.1.1)  
--------------------------------------------  
GIADDR (Gateway IP address)  
0x00000000  
--------------------------------------------  
CHADDR (Client hardware address)  
0x00053C04  
0x8D590000  
0x00000000  
0x00000000  
--------------------------------------------  
192 octets of 0s; BOOTP legacy.  
--------------------------------------------  
Magic cookie  
0x63825363  
--------------------------------------------  
DHCP options  
0x350103       53(DHCP Message Type)  
               1(len)  
               3(request)  
0x3204c0a80081 50(requested IP)  
               4(len)  
               192.168.0.129(requested IP)  
--------------------------------------------  
  
  
4.DHCP ACK   
--------------------------------------------  
Octet 0     Octet 1 	Octet 2 	Octet 3  
--------------------------------------------  
OP   	    HTYPE 	    HLEN 	    HOPS  
0x02 	    0x01 	    0x06 	    0x00  
--------------------------------------------  
XID  
0x3903F326  
--------------------------------------------  
SECS 	                FLAGS  
0x0000 	                0x0000  
--------------------------------------------  
CIADDR (Client IP address)  
0x00000000  
--------------------------------------------  
YIADDR (Your IP address)  
0xC0A80164 (192.168.1.100)  
--------------------------------------------  
SIADDR (Server IP address)  
0xC0A80101 (192.168.1.1)  
--------------------------------------------  
GIADDR (Gateway IP address switched by relay)  
0x00000000  
--------------------------------------------  
CHADDR (Client hardware address)  
0x00053C04  
0x8D590000  
0x00000000  
0x00000000  
--------------------------------------------  
192 octets of 0s. BOOTP legacy  
--------------------------------------------  
Magic cookie  
0x63825363  
--------------------------------------------  
DHCP options  
0x350105               53 (DHCP Message Type)  
                       1 (len)  
                       5 (DHCP ACK) or 6 (DHCP NAK)  
0x0104ffffff001        1 (subnet mask)  
                       4 (len)  
                       255.255.255.0 (mask)  
0x0304c0a80001         3 (Router)  
                       4 (len)  
                       192.168.1.1 (router)  
0x3604c0a80001         54 (DHCP server identifier)  
                       4 (len)  
                       192.168.1.1 (DHCP Server)  
0x0608ca6a0014ca6a2e97 6 (DNS servers)  
                       8 (len)  
                       202.106.0.20  
                       202.106.46.151  
--------------------------------------------  
</pre>  
  
## Troubleshooting  
当主机请求DHCP失败时，通常会被分配一个169.254.x.x的IP地址。    
