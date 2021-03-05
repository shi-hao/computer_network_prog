#!/bin/bash

# airmon-ng :  Enable and disable monitor mode on wireless interfaces.
# airmon-ng check : Checking for interfering processes
# airmon-ng check kill : This command stops network managers then kill interfering processes left
sudo airmon-ng check kill

################################################
# choose network interfaces
source ../my_tools/my_function.sh

my_if=''
chose_if my_if
################################################

# airmon-ng start [nic] : Enable monitor mode 
# airmon-ng stop [nic]  : Disable monitor mode
sudo airmon-ng start $my_if
