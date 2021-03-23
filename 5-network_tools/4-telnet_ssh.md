# Login By Network

**Login to remote host!**  

**telnet**  
**ssh**  

## telnet
telnet是一个应用协议用于提供命令行接口，使用TCP协议。
默认情况下，使用TCP的23端口。

telnet [ip or domain]  [port]

## ssh
Secure Shell
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
使用SSH工具登录服务器时，可以选择使用服务器的用户名和密码来验证登录，这种
登录方式安全等级较低，使用密钥对登录更加安全，而且配置好密钥对后，可以直接
登录，不需要输入密码，更加方便。
SSH客户端使用非对称算法（默认RSA）生成密钥对，然后将生成的公钥保存到服务端，
客户端在登录时，使用本地保存的私钥和服务端交互信息来进行身份认证。
使用密钥生成工具在客户端生成密钥对。
<pre>
ssh-keygen
</pre>
在用户目录.ssh/下生成公钥和私钥，id_rsa  id_rsa.pub
将id_rsa.pub公钥拷贝到服务端目录.ssh/authorized_keys文件内。

(3)SSH修改TCP服务端口
vim /etc/ssh/sshd_config
<pre>
# Package generated configuration file
# See the sshd_config(5) manpage for details

# What ports, IPs and protocols we listen for
Port 22
</pre>

(4)SSH修改认证模式
vim /etc/ssh/sshd_config
