#!/bin/bash

## restart the strongSwan service and enable it to start at reboot
systemctl restart strongswan
systemctl disable strongswan

sleep 5

## verify the status of the strongSwan service
systemctl status strongswan
