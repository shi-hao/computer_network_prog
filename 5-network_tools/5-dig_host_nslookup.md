# domain name and DNS

## Get IP address from the domain name  
(1)dig  
get the ip address from domain name, only output the ip address     
dig +short [domain_name]  
for example:  
dig +short www.example.com   
  
get ip address from domain name using specific dns server, only output ip address     
dig +short [domain_name] @[dns_server]  
for example:  
dig +short www.example.com @resolver1.opendns.com  
dig +short www.example.com @114.114.114.114  
  
  
(2)host  
get ip address from domain name    
host [domain]  
  
get ip address from domain name using specific dns server   
host [domain] [dns]  
  
(3)nslookup  
get ip address from domain name   
nslookup [domain]  
  
get ip address from domain name using specific dns server   
nslookup [domain] [dns]  
