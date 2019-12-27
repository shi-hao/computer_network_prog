# link to remote host

## ping
判断主机是否在线的工具。
ping [host_ip]

ping成功，说明主机目前在线。
ping失败，说明主机可能不在线，也可能是主机在线，但是禁掉了ICMP回包，或者某个网关，防火墙过滤了ICMP包。


## telnet
telnet是一个应用协议用于提供命令行接口，使用TCP协议。
默认情况下，使用TCP的23端口。

telnet [ip or domain]  [port]

## ssh
Secure Shell，简单的理解 ssh = telnet + ssl
默认情况下，使用TCP的22端口，也可以指定端口。

ssh [user_name]@[ip]
ssh [user_name]@[ip] -p [port] -i [key]

比如：
ssh root@192.168.1.1 -p 40

(1)SSH配置登录信息
ubuntu在用户目录下，会有个ssh的配置信息文件夹，通常是~/.ssh/
如果经常要登录某台网络设备，可以在该文件夹下创建config文件，将登录信息
写到此文件下面，以后可以通过读取配置文件登录，非常方便。
配置格式如下：
<pre>
Host      server   #配置名称
Hostname  ip       #网络设备ip地址
Port      num      #端口号
User	  用户名   #用户名
</pre>
配置好后，保存，下次可以直接使用ssh  server来登录设备，同时可以使用tab键
来补全，非常方便。

(2)SSH使用密钥对登录

(3)SSH修改TCP服务端口
vim /etc/ssh/sshd_config
<pre>
# Package generated configuration file
# See the sshd_config(5) manpage for details

# What ports, IPs and protocols we listen for
Port 22
</pre>
