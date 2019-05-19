# udp hole punching example
A simple UDP hole punching example originally taken from
http://www.rapapaing.com/blog/?p=24.
To use it you need to set SRV_IP in client_udp.c.

A drawback is that it always punches the one port
that the server is using to talk to the other client.
It would be better to test the ports above that port
for a higher success rate.

# improve
communication protocol 

--------------------------------------
| opcode     |   payload            |
| 1 byte     |                      |
--------------------------------------

1.client hello 
opcode = 0x00
--------------------------------------
| opcode |   client id          |
| 1 byte |   1 byte             |
--------------------------------------

2.server hello 
opcode = 0x01
--------------------------------------
| opcode |   client endpoint ip info |
| 1 byte |   sock_addr_in = 16 byte  |
--------------------------------------

3.member report
opcode = 0x02
------------------------------------------------------------------------
| opcode |  member sum = s | member id array| member sock_addr_in array|
| 1 byte |  1 byte         | 1byte * s      | 16byte *  s              |
------------------------------------------------------------------------

4.member talk
opcode = 0x03
--------------------------------------------
| opcode |  talk info size = s| talk info|
| 1 byte |  1 byte            | s byte   |
--------------------------------------------

5.ack
opcode = 0x04
-----------
| opcode | 
| 1 byte |
-----------
