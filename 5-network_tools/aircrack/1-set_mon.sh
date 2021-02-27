#!/bin/bash

# airmon-ng :  Enable and disable monitor mode on wireless interfaces.
# airmon-ng check : Checking for interfering processes
# airmon-ng check kill : This command stops network managers then kill interfering processes left

sudo airmon-ng check kill

# airmon-ng start [nic] : Enable monitor mode 
# airmon-ng stop [nic]  : Disable monitor mode
sudo airmon-ng stop wlp4s0
sleep 5
sudo airmon-ng start wlp4s0
