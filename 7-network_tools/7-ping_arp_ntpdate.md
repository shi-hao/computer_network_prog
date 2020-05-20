
## ping
判断主机是否在线的工具。
ping [host_ip]

ping成功，说明主机目前在线。
ping失败，说明主机可能不在线，也可能是主机在线，但是禁掉了ICMP回包，或者某个网
关，防火墙过滤了ICMP包。

## arp
arp -n


# ntpdate  
仅获取ntp server时间，不同步到本地时钟  
<pre>
ntpdate -q [ntp-server]  
</pre>
  
  
# host  
通过域名查看IP信息  
<pre>
host [domain]  
</pre>
