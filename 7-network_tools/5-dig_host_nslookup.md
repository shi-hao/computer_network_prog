# Get IP

**get IP from the domain name**

**dig**
**host**
**nslookup**

## dig
get the ip from domain using, only output the ip 
<pre>
dig +short [domain]

for example:
dig +short www.example.com 
</pre>

get the ip from domain using specific dns server, only output the ip 
<pre>
dig +short [domain] [dns]

for example:
dig +short www.example.com @resolver1.opendns.com
dig +short www.example.com @114.114.114.114
</pre>


## host
get the ip from domain
<pre>
host [domain]
</pre>

get the ip from domain using specific dns server 
<pre>
host [domain] [dns]
</pre>

## nslookup
get the ip from domain
<pre>
nslookup [domain]
</pre>

get the ip from domain using specific dns server 
<pre>
nslookup [domain] [dns]
</pre>
