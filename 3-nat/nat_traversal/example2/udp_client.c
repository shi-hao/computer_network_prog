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
#include <sys/time.h>
#include<signal.h>

#include "protocol.h"

#define BUFLEN 512
#define NPACK 10
//#define PORT 9930
#define PORT 1194

// This is our server's IP address. In case you're wondering, this one is an RFC 5737 address.
//#define SRV_IP "203.0.113.61"
#define  SRV_IP    "39.105.113.152"
#define  SRV_IP_2  "47.93.8.236"
//#define SRV_IP "127.0.0.1"

// Just a function to kill the program when something goes wrong.
void diep(char *s)
{
	perror(s);
	exit(1);
}

//global socket handler 
int s;
group my_group;  //add lock to my_group is more safe
struct sockaddr_in si_server;

//SIGALRM 
void signal_func(){
	char buf[BUFLEN];
	int data_len = 0;
	struct sockaddr_in si_other;
	int slen=sizeof(si_other);

	//send heart_beat
	buf[0] = heart_beat;
	data_len = 1;
	if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_server), slen)==-1)
		diep("sendto()");
	printf("sending heart_beat to server\n");

	//send member talk
	buf[0] = member_talk;
	buf[1] = 2;
	buf[2] = 'h';
	buf[3] = 'i';
	data_len = 4;
	for(int cnt=0; cnt<my_group.pos; cnt++){
		si_other = my_group.member_array[cnt].si;
		printf("sending member talk %s:%d\n", inet_ntoa(si_other.sin_addr), 
				ntohs(si_other.sin_port));
		if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
			diep("sendto()");
	}
	printf("sending member_talk to all members\n");
}

void set_my_timer(){
#define     timer_seconds    4
	int res = 0;
	struct itimerval tick;

	//set SIGALRM response function
	signal(SIGALRM, signal_func);

	//Timeout to run first time
	memset(&tick, 0, sizeof(tick));
	tick.it_value.tv_sec = timer_seconds;
	tick.it_value.tv_usec = 0;

	//After first, the Interval time for clock
	tick.it_interval.tv_sec = timer_seconds;
	tick.it_interval.tv_usec = 0;

	//set timer
	if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
		printf("Set timer failed!\n");
}


int main(int argc, char* argv[])
{
#define     BUFLEN           512
	struct sockaddr_in si_me,si_meme, si_other;
	int slen=sizeof(si_other);
	char buf[BUFLEN];
	int data_len;

	memset(&my_group, 0, sizeof(my_group));
	my_group.capacity = group_size;

	/////////////////////////////////////////////////////////////////////////
	/*
	 *check the nat type
	 */
	//create socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");

	// Our own endpoint data
	memset((char *) &si_me, 0, sizeof(si_me));
	memset((char *) &si_meme, 0, sizeof(si_meme));

	// The server's endpoint data
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	if (inet_aton(SRV_IP_2, &si_other.sin_addr)==0)
		diep("aton");

	//client_hello data
	buf[0] = client_hello;
	buf[1] = 0x10;
	data_len = 2;

	//send client_hello to server 1
	if(sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
		diep("sendto");

	if(recvfrom(s, &buf, sizeof(buf), 0, (struct sockaddr*)(&si_other), &slen)==-1)
		diep("recvfrom");

	char opcode = buf[0];
	if(opcode == server_hello){
		memcpy(&si_me, &buf[1], sizeof(si_me));
		printf("received server_hello, my endpoint %s:%d\n", inet_ntoa(si_me.sin_addr), 
				ntohs(si_me.sin_port));
	}

	//client_hello data
	buf[0] = client_hello;
	buf[1] = 0x10;
	data_len = 2;

	//send client_hello to server 2
	if(inet_aton(SRV_IP, &si_other.sin_addr)==0)
		diep("aton");

	if(sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
		diep("sendto");

	if(recvfrom(s, &buf, sizeof(buf), 0, (struct sockaddr*)(&si_other), &slen)==-1)
		diep("recvfrom");

	if(opcode == server_hello){
		memcpy(&si_meme, &buf[1], sizeof(si_meme));
		printf("received server_hello, my endpoint %s:%d\n", inet_ntoa(si_meme.sin_addr), 
				ntohs(si_meme.sin_port));
	}

	if((si_me.sin_addr.s_addr == si_meme.sin_addr.s_addr) && 
			(si_me.sin_port == si_meme.sin_port)){
		printf("nat type is not symmetric nat, udp hole punching is useful\n");

	}else{
		printf("nat type is symmetric nat, udp hole punching is useless, exit\n");
		exit(0);
	}
	///////////////////////////////////////////////////////////////////

	// Store the server's endpoint data so we can easily discriminate between server and peer datagrams.
	si_server = si_other;

	// Send a simple datagram to the server to let it know of our public UDP endpoint.
	// Not only the server, but other clients will send their data through this endpoint.
	// The datagram payload is irrelevant, but if we wanted to support multiple
	// clients behind the same NAT, we'd send our won private UDP endpoint information
	// as well.
	buf[0] = member_request;
	data_len = 1;
	if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
		diep("sendto");

	set_my_timer();

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
		if (si_server.sin_addr.s_addr == si_other.sin_addr.s_addr && 
				si_server.sin_port == si_other.sin_port)
		{
			char opcode = buf[0];
			if(opcode == server_hello){
				memcpy(&si_me, &buf[1], sizeof(si_me));
				printf("received server_hello, my endpoint %s:%d\n", inet_ntoa(si_me.sin_addr), 
						ntohs(si_me.sin_port));

			}else if(opcode == member_report){
				printf("received member_report\n");
				char size = buf[1];
				int step = sizeof(member);
				my_group.pos = size;
				for(int cnt=0; cnt<size; cnt++){
					memcpy(&(my_group.member_array[cnt]), buf+2+cnt*step, sizeof(member));
				}
				printf("Now we have %d peers\n", my_group.pos);

				//send data
				buf[0] = member_talk;
				buf[1] = 2;
				buf[2] = 'h';
				buf[3] = 'i';
				data_len = 4;
				for(int cnt=0; cnt<my_group.pos; cnt++){
					si_other = my_group.member_array[cnt].si;
					for(int cnt=0; cnt<1; cnt++){
						printf("sending member talk %s:%d\n", inet_ntoa(si_other.sin_addr), 
								ntohs(si_other.sin_port));
						if (sendto(s, buf, data_len, 0, (struct sockaddr*)(&si_other), slen)==-1)
							diep("sendto()");
					}
				}
			}else if(opcode == ack){
				printf("received ack packet\n");
			}
			// And here is where the actual hole punching happens. We are going to send
			// a bunch of datagrams to each peer. Since we're using the same socket we
			// previously used to send data to the server, our local endpoint is the same
			// as before.
			// If the NAT maps our local endpoint to the same public endpoint
			// regardless of the remote endpoint, after the first datagram we send, we
			// have an open session (the hole punch) between our local endpoint and the
			// peer's public endpoint. The first datagram will probably not go through
			// the peer's NAT, but since UDP is stateless, there is no way for our NAT
			// to know that the datagram we sent got dropped by the peer's NAT (well,
			// our NAT may get an ICMP Destination Unreachable, but most NATs are
			// configured to simply discard them) but when the peer sends us a datagram,
			// it will pass through the hole punch into our local endpoint.
		}
		else
		{
			// The datagram came from a peer
			for (int i = 0; i < my_group.pos; i++)
			{
				// Identify which peer it came from
				if ((my_group.member_array[i].si.sin_addr.s_addr ==  si_other.sin_addr.s_addr) &&
						(my_group.member_array[i].si.sin_port == si_other.sin_port))
				{
					//opcode 
					char opcode = buf[0];

					if(opcode == member_talk){
						// And do something useful with the received payload
						printf("Received member_talk from peer %d:%s\n", i, &buf[2]);
						break;
					}
				}
			}

			// It is possible to get data from an unregistered peer. These are some reasons
			// I quickly came up with, in which this can happen:
			// 1. The server's datagram notifying us with the peer's address got lost,
			//    or it hasn't arrived yet (likely)
			// 2. A malicious (or clueless) user is sending you data on this endpoint (maybe
			//    unlikely)
			// 3. The peer's public endpoint changed either because the session timed out,
			//    or because its NAT did not assign the same public endpoint when sending
			//    datagrams to different remote endpoints. If this happens, and we're able
			//    to detect this situation, we could change our peer's endpoint data to
			//    the correct one. If we manage to pull this off correctly, even if at most
			//    one client has a NAT that doesn't support hole punching, we can communicate
			//    directly between both peers.
		}
	}

	// Actually, we never reach this point...
	close(s);
	return 0;
}
