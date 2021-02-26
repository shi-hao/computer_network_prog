#!/bin/bash
#kill airmon-ng process
sudo airmon-ng check kill

# Set monitor mode : 
#	airmon-ng start [nic]
sudo airmon-ng start wlx48022a4f5626
