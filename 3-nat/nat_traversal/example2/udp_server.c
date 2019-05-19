// UDP hole punching example, server code
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

// Just a function to kill the program when something goes wrong.
void diep(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	struct sockaddr_in si_me, si_other;
	char buf[BUFLEN];
	int s, slen=sizeof(si_other);
	group my_group;

	memset(&my_group, 0, sizeof(my_group));
	my_group.capacity = group_size;

	// Create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");

	// si_me stores our local endpoint. Remember that this program
	// has to be run in a network with UDP endpoint previously known
	// and directly accessible by all clients. In simpler terms, the
	// server cannot be behind a NAT.
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (struct sockaddr*)(&si_me), sizeof(si_me))==-1)
		diep("bind");

	while (1)
	{
		// When a new client sends a datagram...
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)(&si_other), &slen)==-1)
			diep("recvfrom");
		// The client's public UDP endpoint data is now in si_other.
		// Notice that we're completely ignoring the datagram payload.
		// If we want to support multiple clients inside the same NAT,
		// we'd have clients send their own private UDP endpoints
		// encoded in some way inside the payload, and store those as
		// well.
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

		//
		if(buf[0] == client_hello){

			//add member
			my_group.member_array[my_group.pos].id = buf[0];
			my_group.member_array[my_group.pos++].si = si_other;

			//server_hello
			buf[0] = server_hello;
			memcpy(&buf[1], &si_other, sizeof(si_other));
			if(sendto(s, buf, 1, 0, (struct sockaddr*)(&si_other), slen)==-1)
				diep("sendto");


			//member report
			buf[0] = member_report;
			buf[1] = my_group.pos;
			int ppos=2;

			//member id
			for(int cnt=0; cnt<my_group.pos; cnt++)
				buf[ppos+cnt] = my_group.member_array[cnt].id;

			ppos += my_group.pos;
			//member sockaddr_in
			for(int cnt=0; cnt<my_group.pos; cnt++)
				memcpy(buf+ppos+cnt*16, &(my_group.member_array[cnt].si), sizeof(si_other));

			//send the all member info to every member
			for(int cnt=0; cnt<my_group.pos; cnt++){
				si_other = my_group.member_array[cnt].si; 
				int len = my_group.pos * sizeof(si_other) + my_group.pos + 2;
				if (sendto(s, buf, len, 0, (struct sockaddr*)(&si_other), slen)==-1)
					diep("sendto");
			}
		}

		printf("Now we have %d clients\n", my_group.pos);
		// And we go back to listening. Notice that since UDP has no notion
		// of connections, we can use the same socket to listen for data
		// from different clients.
	}

	// Actually, we never reach this point...
	close(s);
	return 0;
}
