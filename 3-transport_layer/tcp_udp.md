# TCP/UDP

**Packet**
**TCP/UDP SEQUENCE**
**TCP/UDP PORT**
**TCP/UDP MTU**

## TCP
### Packet
<pre>
TCP Header
--------------------------------------------
|source port number |destination port number|
|2 bytes            |2 bytes                |
---------------------------------------------
|sequence number                            |
|4 bytes                                    |
--------------------------------------------
|acknowlegement number                      |
|4 bytes                                    |
---------------------------------------------
|Header|resvd|flags |window size            |           
|length|     |      |                       |
|4bits |6bits| 6bits|2bytes                 |     
---------------------------------------------
|checksum          | urgent pointer         |
|2 bytes           | 2 bytes                |
--------------------------------------------
|optional data                              |
| 0-40bytes                                 |
--------------------------------------------
|payload(optional)                          |
--------------------------------------------

bits flags:
--------------------------
|URG|ACK|PSH|RST|SYN|FIN|           
|   |   |   |   |   |   |
| 1b|1b |1b |1b |1b |1b |     
--------------------------

source port number:源端口号
destination port number:目的端口号

sequence number:TCP发送序列号
acknowlegement number：TCP应答序列号

header length:TCP头长度，用来区分payload和header

URG: urgent, URG bit is used to treat certain data on an urgent basis
ACK: acknowlegement, ACK bit indicates whether acknowledgement number field is
     valid or not.
PSH: push, PSH bit is used to push the entire buffer immediately to the
     receiving application.
RST: reset, RST bit is used to reset the TCP connection.
SYN: synchronize, SYN bit is used to synchronize the sequence numbers.
FIN: finish, FIN bit is used to terminate the TCP connection.
</pre>

### 3-step handshake
To establish a connection, TCP uses a three-way handshake. Before a client  
attempts to connect with a server, the server must first bind to and listen at  
a port to open it up for connections: this is called a passive open. Once the  
passive open is established, a client may initiate an active open. To  
establish a connection, the three-way (or 3-step) handshake occurs:   
  
SYN: The active open is performed by the client sending a SYN to the  
	 server. The client sets the segment's sequence number to a random value A.  
  
SYN-ACK: In response, the server replies with a SYN-ACK. The acknowledgment number   
         is set to one more than the received sequence number A+1, and the   
		 sequence number that the server chooses for the packet is another random number, B.  
  
ACK: Finally, the client sends an ACK back to the server. The sequence number is set to   
	 the received acknowledgement value A+1, and the acknowledgement number is set   
	 to one more than the received sequence number B+1.  
	
TCP正式通信之前，需要先建立连接，通过三步建立连接。
前提：server端要在指定的IP和端口下监听连接。
(1)client发起连接请求，发送SYN报文给server，SYN标志位置1，sequence number选
   择一个随机数A作为序列号，一般是0。
(2)server回应一条SYN+ACK报文，SYN标志位置1，ACK标志位置1，sequence number选
   择一个随机数B作为序列号，一般是0，acknowlegement number设置为B+1。
(3)client回应一条ACK报文，ACK标志位置1，sequence number置为A+1，acknowlegement
   number标志位置为B+1

### communication
(1)PUSH+ACK
正常通信一般使用的是PUSH+ACK报文，即PUSH和ACK标志位置1。
(2)sequence number和acknowlegement number
当连接建立，开始传输数据后，server和client双方各自维护自己的序列号，序列号如何
选择呢，双方对自己发送的每一个字节数据按照发送顺序进行编号，比如client发送一个
长度为20字节的数据包，即payload为20字节，那么字节编号就是1到20，数据包的
sequence number是payload的首个字节的编号，即1，当server收到数据包后，ACK应答包
的acknowlegement number是收到payload字节总数加上1，即21。
(3)批量确认和滑动窗口机制
TCP数据包是可以批量确认的，比如发送方在没有收到ACK之前，可以发送多个数据包，然
后接收端收到多个数据包后，回复一个ACK数据包来确认所有数据包都收到了。
???????????滑动窗口?????????????????????????
(4)丢包检测
当发送方发送一组长度为300字节的数据到接收方，但是接收方回应的acknowlegement
number大小不是301，或者直接没有ACK，那么发送方则知道数据丢包了，启动重发机制。

### reset

### finish 

<pre>
UDP Header
--------------------------------------------
|source port number |destination port number|
|2 bytes            |2 bytes                |
---------------------------------------------
|length             |checksum               |
|2 bytes            |2 bytes                |
---------------------------------------------
</pre>

## TCP Sequence


## Port


## TCP/UDP MTu
