# iptables
Iptables is an extremely flexible firewall utility built for Linux operating
systems. Whether you’re a novice Linux geek or a system administrator, there’s
probably some way that iptables can be a great use to you. Read on as we show
you how to configure the most versatile Linux firewall.

## About iptables
iptables is a command-line firewall utility that uses policy chains to allow
or block traffic. When a connection tries to establish itself on your system,
iptables looks for a rule in its list to match it to. If it doesn’t find
one, it resorts to the default action.

iptables almost always comes pre-installed on any Linux distribution. To
update/install it, just retrieve the iptables package:

sudo apt-get install iptables

There are GUI alternatives to iptables like Firestarter, but iptables isn’t
really that hard once you have a few commands down. You want to be extremely
careful when configuring iptables rules, particularly if you’re SSH’d into a
server, because one wrong command can permanently lock you out until it’s
manually fixed at the physical machine.

## Types of Chains
iptables uses three different chains: input, forward, and output.

Input – This chain is used to control the behavior for incoming connections.
For example, if a user attempts to SSH into your PC/server, iptables will
attempt to match the IP address and port to a rule in the input chain.

Forward – This chain is used for incoming connections that aren’t actually
being delivered locally. Think of a router – data is always being sent to it
but rarely actually destined for the router itself; the data is just forwarded
to its target. Unless you’re doing some kind of routing, NATing, or something
else on your system that requires forwarding, you won’t even use this chain.

There’s one sure-fire way to check whether or not your system uses/needs the
forward chain.

iptables -L -v

The screenshot above is of a server that’s been running for a few weeks and
has no restrictions on incoming or outgoing connections. As you can see, the
input chain has processed 11GB of packets and the output chain has processed
17GB. The forward chain, on the other hand, has not needed to process a single
packet. This is because the server isn’t doing any kind of forwarding or being
used as a pass-through device.

Output – This chain is used for outgoing connections. For example, if you try
to ping howtogeek.com, iptables will check its output chain to see what the
rules are regarding ping and howtogeek.com before making a decision to allow
or deny the connection attempt.

## Policy Chain Default Behavior

