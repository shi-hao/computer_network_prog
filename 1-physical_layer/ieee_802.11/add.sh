#!/bin/bash

sudo iw dev wlp4s0 interface add mon0 type monitor
sudo ifconfig mon0 up
