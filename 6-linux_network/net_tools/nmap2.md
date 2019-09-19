# namp usefull command  
  
  
## host up  
nmap使用icmp来判断主机是否在线。  
  
## tcp/udp port scanning state  
  
TCP PORT SCANNING  
-sS(TCP SYN scan)  
<pre>  
open      目标主机回应(TCP SYN+ACK)，说明目标主机端口开放，并有服务在端口监听。  
  
close     目标主机回应(TCP RESET)，说明目标主机端口开放，但是没有服务在端口监听。  
  
filtered  目标主机没有回应，或者收到ICMP不可达数据包(type 3, code 0, 1, 2, 3, 9, 10, or 13)，  
          目标主机不可达。  
</pre>  
  
UDP PORT SCANNING  
-sU(UDP scan)  
<pre>  
open          目标主机回应UDP数据包，说明目标主机端口开放，并有服务在端口监听。  
  
close         收到ICMP不可达数据包(ype 3, code 3)，说明目标主机端口开放，但是没有服务在监听。  
  
filtered      收到ICMP不可达数据包(type 3, codes 0, 1, 2, 9, 10, or 13)，说明目标主机不可达。  
  
open|filtered 目标主机没有回应，无法确定目标主机状态。  
</pre>  
  
-Pn  
默认目标主机是在线的。当主机屏蔽ICMP时，强制使用此选项来扫描端口。  
  
-p  port1  
-p  port1,port2  
-p  port1-port2  
指定扫描的端口号或者端口区间  
