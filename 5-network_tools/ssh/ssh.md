ssh access github  
  
正常情况下，本地主机生成key，并添加到github，一直正常访问，突然有一天出现如下问题：  
sign_and_send_pubkey: signing failed: agent refused operation  
git@github.com: Permission denied (publickey).  
fatal: Could not read from remote repository.  
使用ssh -T git@github.com测试，报同样错误。  
  
匪夷所思，回想起来，自己做过如下操作，  
（１）chmod -R 755 ./  在home/usr路径下执行了该操作，修改了整个文件夹下文件的权限。  
（２）git config --global core.quotepath false 因为git在terminal上显示中文是数字编码，所以做了如上操作。  
  
刚开始以为因为设置git config的原因，导致是不是生成的key和本地的git用户配置不匹配了，导致无法连接上git，  
所以重新生成了key，并添加到github，结果问题依旧。  
必应之后，发现引起该问题的原因是ssh-agent已经没有附加任何的key，使用ssh-add手动添加key，结果报如下错误，  
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  
@         WARNING: UNPROTECTED PRIVATE KEY FILE!          @  
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  
Permissions 0744 for '/home/bleach/.ssh/id_rsa' are too open.  
It is required that your private key files are NOT accessible by others.  
This private key will be ignored.  
意思说是私钥权限设置其他用户可以访问，但是ssh-add拒绝添加该密钥，所以，tmd，  
修改权限，问题解决。  
