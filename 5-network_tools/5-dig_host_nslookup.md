# DNS  
  
## What is DNS?  
DNS:Domain Name System  
  
how to get the local dns config???     
  
## Get IP address from the domain name  
(1)dig  
get the ip from domain name, only output the ip address     
<pre>  
dig +short [domain_name]  
  
for example:  
dig +short www.example.com   
</pre>  
  
get ip address from domain name using specific dns server, only output ip address     
<pre>  
dig +short [domain_name] @[dns_server]  
  
for example:  
dig +short www.example.com @resolver1.opendns.com  
dig +short www.example.com @114.114.114.114  
</pre>  
  
  
(2)host  
get ip address from domain name    
<pre>  
host [domain]  
</pre>  
  
get the ip from domain using specific dns server   
<pre>  
host [domain] [dns]  
</pre>  
  
(3)nslookup  
get the ip from domain  
<pre>  
nslookup [domain]  
</pre>  
  
get the ip from domain using specific dns server   
<pre>  
nslookup [domain] [dns]  
</pre>  
