IPERF  
The ultimate speed test tool for TCP, UDP and SCTP  
实用的TCP，UDP，SCTP测试工具。  
官方网站：https://iperf.fr/en/  
  
1.使用iperf测试udp组播  
(1)从官网下载iperf，搭建测试环境，本次实验环境的网络拓扑如下。  
  
<pre>
--------  
|router|  
-----------------------------------------  
||                            ||  
-----                         ----  
|PC1|                         |pc2|  
-----                         -----  
ubuntu16.04+iperf v2.0.5      win10+iperf v2.0.8  
192.168.3.3                   192.168.3.5  
</pre>
  
(2)iperf安装  
win   :解压出压缩包后，将文件直接拷贝到/windowd/system32目录下，打开cmd界面，直接运行iperf。  
ubuntu:直接使用apt-get install iperf  
  
(3)实测  
ubuntu主机运行multicast接收程序:  
iperf -s -u  -B 239.1.1.88  -f m  -i  1  
  
-f 表示单位，此处为兆  
-s 表示运行服务端  
-u 表示使用udp  
-B 表示使用的网卡接口  
-i Sets the interval time in seconds between periodic bandwidth, jitter, and loss reports.  
-T 等同于--ttl  
此处的-B指定的是组播地址，可以使用netstat -gn查看指定的网卡是否加入了组播地址,目前iperf在server模式下  
组播不支持指定网卡接收，所以请注意netstat -gn查看加入组播的网卡。  
  
win主机运行multicast发送程序：  
iperf -c 239.1.1.88 -B 192.168.3.3 -b 50m -u -T 32 -t 3 -i 1  
  
  
-t 表示测试总时间  
-i 表示时间间隔。  
比如 -t 3 -i 1 就表示发送3秒的数据包，间隔1秒  
  
-b Set target bandwidth to n bits/sec (default 1 Mbit/sec for UDP, unlimited for TCP).  
   设置测试带宽，此处为50兆  
  
  
troubleshooting  
  
(1)win10:bind failed can not assign request address  
解决办法：使用不依赖cygwin编译的版本，比如win32 2.08版本。  
  
(2)iperf 指定网卡接口  
iperf在运行时，client模式，可以使用-B指定具体的网卡发送数据。  
但是在server模式下，运行组播模式，-B用来指定组播地址，无法指定具体的网卡接收组播数据，一般而言如果有线和无线  
网卡都启用了，iperf会默认使用有线网卡，所以可以通过禁用网卡来让iperf使用我们预意向的网卡  
  
-------------------------------------------------------------------------------------------  
iperf官网组播演示例子：  
Multicast  
  
To test multicast, run several servers with the bind option (-B, --bind) set to the multicast group address.  
Run the client, connecting to the multicast group address and setting the TTL (-T, --ttl) as needed.   
Unlike normal TCP and UDP tests, multicast servers may be started after the client. In that case,   
datagrams sent before the server started show up as losses in the first periodic report   
(61 datagrams on arno below).  
  
node5> iperf -c 224.0.67.67 -u --ttl 5 -t 5  
------------------------------------------------------------  
Client connecting to 224.0.67.67, UDP port 5001  
Sending 1470 byte datagrams  
Setting multicast TTL to 5  
UDP buffer size: 32.0 KByte (default)  
------------------------------------------------------------  
[  3] local <IP Addr node5> port 1025 connected with 224.0.67.67 port 5001  
[ ID] Interval       Transfer     Bandwidth  
[  3]  0.0- 5.0 sec   642 KBytes   1.0 Mbits/sec  
[  3] Sent 447 datagrams  
  
node5> iperf -s -u -B 224.0.67.67 -i 1  
------------------------------------------------------------  
Server listening on UDP port 5001  
Binding to local address 224.0.67.67  
Joining multicast group  224.0.67.67  
Receiving 1470 byte datagrams  
UDP buffer size: 32.0 KByte (default)  
------------------------------------------------------------  
	[  3] local 224.0.67.67 port 5001 connected with <IP Addr node5> port 1025  
	[ ID] Interval       Transfer     Bandwidth       Jitter   Lost/Total Datagrams  
	[  3]  0.0- 1.0 sec   131 KBytes   1.0 Mbits/sec  0.007 ms    0/   91 (0%)  
	[  3]  1.0- 2.0 sec   128 KBytes   1.0 Mbits/sec  0.008 ms    0/   89 (0%)  
	[  3]  2.0- 3.0 sec   128 KBytes   1.0 Mbits/sec  0.010 ms    0/   89 (0%)  
	[  3]  3.0- 4.0 sec   128 KBytes   1.0 Mbits/sec  0.013 ms    0/   89 (0%)  
	[  3]  4.0- 5.0 sec   128 KBytes   1.0 Mbits/sec  0.008 ms    0/   89 (0%)  
	[  3]  0.0- 5.0 sec   642 KBytes   1.0 Mbits/sec  0.008 ms    0/  447 (0%)  
  
node6> iperf -s -u -B 224.0.67.67 -i 1  
------------------------------------------------------------  
Server listening on UDP port 5001  
Binding to local address 224.0.67.67  
Joining multicast group  224.0.67.67  
Receiving 1470 byte datagrams  
UDP buffer size: 60.0 KByte (default)  
------------------------------------------------------------  
    [  3] local 224.0.67.67 port 5001 connected with <IP Addr node5> port 1025  
    [ ID] Interval       Transfer     Bandwidth       Jitter   Lost/Total Datagrams  
    [  3]  0.0- 1.0 sec   129 KBytes   1.0 Mbits/sec  0.778 ms   61/  151 (40%)  
    [  3]  1.0- 2.0 sec   128 KBytes   1.0 Mbits/sec  0.236 ms    0/   89 (0%)  
    [  3]  2.0- 3.0 sec   128 KBytes   1.0 Mbits/sec  0.264 ms    0/   89 (0%)  
    [  3]  3.0- 4.0 sec   128 KBytes   1.0 Mbits/sec  0.248 ms    0/   89 (0%)  
    [  3]  0.0- 4.3 sec   554 KBytes   1.0 Mbits/sec  0.298 ms   61/  447 (14%)  
  
Start multiple clients or servers as explained above, sending data to the same multicast server.   
(If you have multiple servers listening on the multicast address, each of the servers will be getting the data)  
