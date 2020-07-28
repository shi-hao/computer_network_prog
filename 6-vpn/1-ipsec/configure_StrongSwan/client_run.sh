#!/bin/bash
# restart the strongSwan service
systemctl restart strongswan

sleep 5

# check the VPN connection status using the following command
sudo ipsec status
