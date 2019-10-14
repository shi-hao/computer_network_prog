# link to remote host

## ping
判断主机是否在线的工具。
ping [host_ip]

ping成功，说明主机目前在线。
ping失败，说明主机可能不在线，也可能是主机在线，但是禁掉了ICMP回包，或者某个网关，防火墙过滤了
ICMP包。


## telnet
telnet是一个应用协议用于提供命令行接口，使用TCP协议。
默认情况下，使用TCP的23端口。

tlenet [ip or domain]  [port]


## ssh
Secure Shell，简单的理解 ssh = telnet + ssl
默认情况下，使用TCP的22端口

ssh user_name@[ip]
