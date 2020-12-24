# Setting up a dummy interface

If you want to create network interfaces, but lack a physical NIC to back it,
you can use the dummy link type. You can read more about them here:iproute2 
Wikipedia page.

## Creating eth10
To make this interface you'd first need to make sure that you have the dummy
kernel module loaded. You can do this like so:

$ sudo lsmod | grep dummy
$ sudo modprobe dummy
$ sudo lsmod | grep dummy
dummy                  12960  0 

With the driver now loaded you can create what ever dummy network interfaces
you like:

$ sudo ip link add eth10 type dummy

NOTE: In older versions of ip you'd do the above like this, appears to have
changed along the way. Keeping this here for reference purposes, but based on
feedback via comments, the above works now.

$ sudo ip link set name eth10 dev dummy0

And confirm it:

$ ip link show eth10
6: eth10: <BROADCAST,NOARP> mtu 1500 qdisc noop state DOWN mode DEFAULT group default 
    link/ether c6:ad:af:42:80:45 brd ff:ff:ff:ff:ff:ff

## Changing the MAC
You can then change the MAC address if you like:

$ sudo ifconfig eth10 hw ether 00:22:22:ff:ff:ff
$ ip link show eth10
6: eth10: <BROADCAST,NOARP> mtu 1500 qdisc noop state DOWN mode DEFAULT group
default 
    link/ether 00:22:22:ff:ff:ff brd ff:ff:ff:ff:ff:ff

## Creating an alias
You can then create aliases on top of eth10.

$ sudo ip addr add 192.168.100.199/24 brd + dev eth10 label eth10:0

And confirm them like so:

$ ifconfig -a eth10
eth10: flags=130<BROADCAST,NOARP>  mtu 1500
        ether 00:22:22:ff:ff:ff  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

$ ifconfig -a eth10:0
eth10:0: flags=130<BROADCAST,NOARP>  mtu 1500
        inet 192.168.100.199  netmask 255.255.255.0  broadcast 192.168.100.255
        ether 00:22:22:ff:ff:ff  txqueuelen 0  (Ethernet)

Or using ip:

$ ip a | grep -w inet
    inet 127.0.0.1/8 scope host lo
    inet 192.168.1.20/24 brd 192.168.1.255 scope global wlp3s0
    inet 192.168.122.1/24 brd 192.168.122.255 scope global virbr0
    inet 192.168.100.199/24 brd 192.168.100.255 scope global eth10:0

## Removing all this?
If you want to unwind all this you can run these commands to do so:

$ sudo ip addr del 192.168.100.199/24 brd + dev eth10 label eth10:0
$ sudo ip link delete eth10 type dummy
$ sudo rmmod dummy
