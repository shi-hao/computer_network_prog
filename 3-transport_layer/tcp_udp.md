# TCP/UDP

**Packet**
**TCP/UDP SEQUENCE**
**TCP/UDP PORT**
**TCP/UDP MTU**

## Packet
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
--------------------------------------------------
|Header|resvd|URG|ACK|PSH|RST|SYN|FIN|window size|           
|length|     |   |   |   |   |   |   |           |
|4bits |6bits| 1b|1b |1b |1b |1b |1b |2bytes     |     
--------------------------------------------------
|checksum          | urgent pointer         |
|2 bytes           | 2 bytes                |
--------------------------------------------
|optional data                              |
| 0-40bytes                                 |
--------------------------------------------
</pre>


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
Connection establishment  
To establish a connection, TCP uses a three-way handshake. Before a client  
attempts to connect with a server, the server must first bind to and listen at  
a port to open it up for connections: this is called a passive open. Once the  
passive open is established, a client may initiate an active open. To  
establish a connection, the three-way (or 3-step) handshake occurs:   
  
SYN: The active open is performed by the client sending a SYN to the  
	 server. The client sets the segment's sequence number to a random value A.  
  
SYN-ACK: In response, the server replies with a SYN-ACK. The acknowledgment number   
         is set to one more than the received sequence number i.e. A+1, and the   
		 sequence number that the server chooses for the packet is another random number, B.  
  
ACK: Finally, the client sends an ACK back to the server. The sequence number is set to   
	 the received acknowledgement value i.e.A+1, and the acknowledgement number is set   
	 to one more than the received sequence number i.e. B+1.  


## Port


## TCP/UDP MTu
