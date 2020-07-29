#!/bin/bash

# step 1-Install strongSwan
sudo apt install strongswan libcharon-extra-plugins

# step 2-Setting Up a Certificate Authority
## generate a private key for self-signing the CA certificate using a PKI
## utility
ipsec pki --gen --size 4096 --type rsa --outform pem > ca.key.pem

## create your root certificate authority and use the above key to sign the
## root certificate
ipsec pki --self --in ca.key.pem --type rsa --dn "CN=VPN Server CA" --ca --lifetime 3650 --outform pem > ca.cert.pem

## create a private key for the VPN server with the following command
ipsec pki --gen --size 4096 --type rsa --outform pem > server.key.pem

## generate the server certificate by running the following command
ipsec pki --pub --in server.key.pem --type rsa | ipsec pki --issue --lifetime 2750 --cacert ca.cert.pem --cakey ca.key.pem --dn "CN=vpn.example.com" --san="vpn.example.com" --flag serverAuth --flag ikeIntermediate --outform pem > server.cert.pem

## copy the above certificate in the respective IPSec certificates directories as shown below
mv ca.cert.pem /etc/ipsec.d/cacerts/
mv server.cert.pem /etc/ipsec.d/certs/
mv ca.key.pem /etc/ipsec.d/private/
mv server.key.pem /etc/ipsec.d/private/

# step 3-Configure strongSwan
## rename the default configuration file, run the following command
mv /etc/ipsec.conf /etc/ipsec.conf.bak

## move the configuration to the /etc directory
cp ./s_ipsec.conf  /etc/ipsec.conf

# step 4-Configure Authentication
## move the authentication file to /etc directory
cp ./s_ipsec.secrets  /etc/ipsec.secrets
