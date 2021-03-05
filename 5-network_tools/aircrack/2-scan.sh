#!/bin/bash

# airodump-ng : Capture raw 802.11 frames.

#########################################
# choose network interfaces
source ../my_tools/my_function.sh

my_if=''
chose_if my_if
#########################################

# Scan all the access points
#	airodump-ng [monitor_nic]
sudo airodump-ng $my_if
