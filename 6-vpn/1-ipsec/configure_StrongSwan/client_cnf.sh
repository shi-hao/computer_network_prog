#!/bin/bash

# install strongSwan
sudo apt install strongswan libcharon-extra-plugins


# disable the strongSwan service to start at boot
systemctl disable strongswan

# copy the ca.cert.pem file from the VPN server
sudo scp -P 20000 root@39.105.113.152:/etc/ipsec.d/cacerts/ca.cert.pem  /etc/ipsec.d/cacerts/

# move the ipsec.conf
sudo cp ./c_ipsec.conf  /etc/ipsec.conf

# movw the ipsec.secrets
sudo cp ./c_ipsec.secrets  /etc/ipsec.secrets

# restart the strongSwan service
systemctl restart strongswan

# check the VPN connection status using the following command
sudo ipsec status
