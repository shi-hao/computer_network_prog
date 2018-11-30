#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <netdb.h>


int main(int argc, char **argv)
{
	int status;
	struct addrinfo hints, *res, *this;
	char ipaddr[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;     /* AF_INET(IPv4) AF_INET6(IPv6) */
	hints.ai_socktype = SOCK_STREAM; /* TCP stream sockets */

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res))) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for(this = res; this != NULL; this = this->ai_next) {
		void *addr;
		char *ipver;

		if (this->ai_family == AF_INET) { /* IPv4 */
			struct sockaddr_in *ipv4;

			ipv4 = (struct sockaddr_in *)this->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else { /* IPv6 */
			struct sockaddr_in6 *ipv6;

			ipv6 = (struct sockaddr_in6 *)this->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		/* convert the IP to a string and print it */
		inet_ntop(this->ai_family, addr, ipaddr, sizeof(ipaddr));
		printf("%s:\t%s\n", ipver, ipaddr);
	}

	return 0;
}
