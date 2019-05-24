// UDP hole punching example, client code
// Base UDP code stolen from http://www.abc.se/~m6695/udp.html
// By Oscar Rodriguez
// This code is public domain, but you're a complete lunatic
// if you plan to use this code in any real program.

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

#define BUFLEN 512
#define NPACK 10
//#define PORT 9930
#define PORT 1194

// This is our server's IP address. In case you're wondering, this one is an RFC 5737 address.
//#define SRV_IP "203.0.113.61"
#define SRV_IP "39.105.113.152"
//#define SRV_IP "127.0.0.1"
#define SRV_IP_2 "47.93.8.236"

// Just a function to kill the program when something goes wrong.
void diep(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char* argv[])
{
#define   BUFLEN   512
	struct sockaddr_in si_me, si_other, si_server;
	int s, slen=sizeof(si_other);
	char buf[BUFLEN];
	int data_len;
	group my_group;

	memset(&my_group, 0, sizeof(my_group));
	my_group.capacity = group_size;

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");

	// Our own endpoint data
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT); // This is not really necessary, we can also use 0 (any port)
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	// The server's endpoint data
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	if (inet_aton(SRV_IP, &si_other.sin_addr)==0)
		diep("aton");

	//send client_hello to 2 public ip server 
	buf[0] = client_hello;
	buf[1] = 0x10;
	data_len = 2;
	if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
		diep("sendto");

	if (inet_aton(SRV_IP_2, &si_other.sin_addr)==0)
		diep("aton");

	if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
		diep("sendto");

	// Right here, our NAT should have a session entry between our host and the server.
	// We can only hope our NAT maps the same public endpoint (both host and port) when we
	// send datagrams to other clients using our same private endpoint.
	while (1)
	{
		//init the buf
		memset(buf, 0, sizeof(buf));

		// Receive data from the socket. Notice that we use the same socket for server and
		// peer communications. We discriminate by using the remote host endpoint data, but
		// remember that IP addresses are easily spoofed (actually, that's what the NAT is
		// doing), so remember to do some kind of validation in here.
		//if (recvfrom(s, &buf, sizeof(buf), 0, (struct sockaddr*)(&si_other), &slen)==-1)
		if (recvfrom(s, &buf, sizeof(buf), 0, (struct sockaddr*)(&si_other), &slen)==-1)
			diep("recvfrom");
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), 
				ntohs(si_other.sin_port));
		char opcode = buf[0];
		if(opcode == server_hello){
			memcpy(&si_me, &buf[1], sizeof(si_me));
			printf("received server_hello, my endpoint %s:%d\n", inet_ntoa(si_me.sin_addr), 
					ntohs(si_me.sin_port));

		}
	}

	// Actually, we never reach this point...
	close(s);
	return 0;
}
