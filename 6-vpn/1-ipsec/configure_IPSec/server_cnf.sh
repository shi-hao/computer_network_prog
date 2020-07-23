#!/bin/bash

# install strongSwan
sudo apt install strongswan libcharon-extra-plugins

sudo systemctl status strongswan.service
sudo systemctl is-enabled strongswan.service
