#/bin/bash

# How to get the public ip after nat?
# 有很多的方法获取当前主机的公网IP地址。
#
# 解决这个问题的思路很简单，公网上有一台服务器，让当前主机ping下公网服务器
# 抓包看下，就可以知道当前主机的IP地址。
#
# (1)使用现有网络服务
# 现在有很多网站提供查询本地公网IP的服务，打开浏览器，搜索相关服务，即可以知道
# 本地的nat后的公网IP。
# 比如，打开浏览器百度搜索“本地IP”，或者地址栏输入ipecho.net，或者ifconfig.me
#
# (2)使用一些工具通过第三方网站获取
# 比如dig工具，
# dig +short myip.opendns.com @resolver1.opendns.com
# 比如curl
# curl ifconfig.me
#
# (3)登陆网关设备查看地址
# 可以登陆网关设备，查看路由器的公网IP
#
# (4)使用公网服务器
# 远程登陆公网服务器，本地主机ping公网主机，抓包查看IP。
# 
# traceroute是否可以查看公网IP呢？
# traceroute是不可以查看公网IP的，可以实践下。

source ./lib/my_stdio.sh

curl ifconfig.me
