#!/bin/bash 
sudo scp -P 20000 root@39.105.113.152:/etc/ipsec.d/cacerts/ca.cert.pem  /etc/ipsec.d/cacerts/
systemctl restart strongswan
#sudo ipsec up ipsec-ikev2-vpn-client 

