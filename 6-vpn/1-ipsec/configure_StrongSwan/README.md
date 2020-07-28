# StrongSwan

## site to site 
server:
云服务器，NAT网关地址39.105.113.1xx，本地IP地址172.17.79.117，修改NAT网关规则，
允许UDP端口500(IKE)和4500(UDP Encapsulation ESP)转发到主机。

client:
局域网主机，办公室网络，通过网关上网，本地IP地址192.168.0.100
