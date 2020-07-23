#!/bin/bash

# install strongSwan
apt install strongswan libcharon-extra-plugins

# create dir
mkdir -p ~/pki/{cacerts,certs,private}
chmod 700 ~/pki

# Creating a Certificate Authority
pki --gen --type rsa --size 4096 --outform pem > ~/pki/private/ca-key.pem
pki --self --ca --lifetime 3650 --in ~/pki/private/ca-key.pem \
		--type rsa --dn "CN=VPN root CA" --outform pem > ~/pki/cacerts/ca-cert.pem

# Generating a Certificate for the VPN Server
pki --gen --type rsa --size 4096 --outform pem > ~/pki/private/server-key.pem
pki --pub --in ~/pki/private/server-key.pem --type rsa \
    | pki --issue --lifetime 1825 \
        --cacert ~/pki/cacerts/ca-cert.pem \
        --cakey ~/pki/private/ca-key.pem \
        --dn "CN=server_domain_or_IP" --san server_domain_or_IP \
        --flag serverAuth --flag ikeIntermediate --outform pem \
    >  ~/pki/certs/server-cert.pem



# generate a VPN server private key and issue a matching certificate using the
# CA created above
ipsec pki --gen --size 4096 --type rsa --outform pem > vpn-server.key.pem

# generate the server certificate by running the command below
ipsec pki --pub --in vpn-server.key.pem --type rsa \ |
ipsec pki --issue --lifetime 2750 \
		  --cacert vpn-ca.cert.pem \
		  --cakey vpn-ca.key.pem \
		  --dn "CN=vpnsvr.example.com" \
		  --san="vpnsvr.example.com" \
		  --flag serverAuth --flag ikeIntermediate --outform pem > vpn-server.cert.pem
# install certificates
mv vpn-ca.cert.pem /etc/ipsec.d/cacerts/
mv vpn-server.cert.pem /etc/ipsec.d/certs/
mv {vpn-ca.key.pem,vpn-server.key.pem} /etc/ipsec.d/private/

