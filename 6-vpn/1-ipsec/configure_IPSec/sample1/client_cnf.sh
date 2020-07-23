#!/bin/bash

# install strongSwan
apt install strongswan libcharon-extra-plugins

systemctl disable strongswan
