#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

#define BUFLEN 255
/*********************************************************************
 *filename: mcastserver.c
 *purpose: ��ʾ�鲥��̵Ļ������裬�鲥�������ˣ��ؼ����ڼ�����
 *tidied by: zhoulifa(zhoulifa@163.com) ������(http://zhoulifa.bokee.com)
 Linux������ Linux֪ʶ������ SOHO�� ������ ���ó�C����
 *date time:2007-01-25 13:20:00
 *Note: �κ��˿������⸴�ƴ��벢������Щ�ĵ�����Ȼ���������ҵ��;
 * ������ѭGPL
 *Thanks to: Google.com
 *Hope:ϣ��Խ��Խ����˹����Լ���������Ϊ��ѧ������չ����
 * �Ƽ�վ�ھ��˵ļ���Ͻ������죡��л�п�Դǰ���Ĺ��ף�
 *********************************************************************/
int main(int argc, char **argv)
{
	struct sockaddr_in peeraddr;//�鲥��ַ�ṹ��

	struct sockaddr_in serveraddr;

	struct in_addr ia;
	int sockfd;
	char recmsg[BUFLEN + 1];
	unsigned int socklen, n;
	struct hostent *group;
	struct ip_mreq mreq;

	/* ���� socket ����UDPͨѶ */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket creating err in udptalk\n");
		exit(1);
	}

	/* ����Ҫ�����鲥�ĵ�ַ */
	bzero(&mreq, sizeof(struct ip_mreq));
	if (argv[1]) {
		if ((group = gethostbyname(argv[1])) == (struct hostent *) 0) {
			perror("gethostbyname");
			exit(errno);
		}
	} else {
		printf
			("you should give me a group address, 224.0.0.0-239.255.255.255\n");
		exit(errno);
	}

	bcopy((void *) group->h_addr, (void *) &ia, group->h_length);
	/* �������ַ */
	bcopy(&ia, &mreq.imr_multiaddr.s_addr, sizeof(struct in_addr));

	/* ���÷����鲥��Ϣ��Դ�����ĵ�ַ��Ϣ */
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	/* �ѱ��������鲥��ַ��������������Ϊ�鲥��Ա��ֻ�м���������յ��鲥��Ϣ */
	if (setsockopt
			(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,
			 sizeof(struct ip_mreq)) == -1) {
		perror("setsockopt");
		exit(-1);
	}

	socklen = sizeof(struct sockaddr_in);
	memset(&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	if (argv[2])
		peeraddr.sin_port = htons(atoi(argv[2]));
	else
		peeraddr.sin_port = htons(7838);
	if (argv[1]) {
		if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0) {
			printf("Wrong dest IP address!\n");
			exit(0);
		}
	} else {
		printf("no group address given, 224.0.0.0-239.255.255.255\n");
		exit(errno);
	}

	/* ���Լ��Ķ˿ں�IP��Ϣ��socket�� */
	if (bind
			(sockfd, (struct sockaddr *) &peeraddr,
			 sizeof(struct sockaddr_in)) == -1) {
		printf("Bind error\n");
		exit(0);
	}


#if 1
	/* ѭ�����������������鲥��Ϣ */
	for (;;) {
		bzero(recmsg, BUFLEN + 1);
		n = recvfrom(sockfd, recmsg, BUFLEN, 0,
				(struct sockaddr *) &peeraddr, &socklen);
		if (n < 0) {
			printf("recvfrom err in udptalk!\n");
			exit(4);
		} else {
			/* �ɹ����յ����ݱ� */
			recmsg[n] = 0;
			printf("peer:%s", recmsg);
		}
	}

#else 

	/* ѭ�������û��������Ϣ�����鲥��Ϣ */
	for (;;) {
		/* �����û����� */
		bzero(recmsg, BUFLEN + 1);
		if (fgets(recmsg, BUFLEN, stdin) == (char *) EOF)
			exit(0);
		/* ������Ϣ */
		if (sendto
				(sockfd, recmsg, strlen(recmsg), 0,
				 (struct sockaddr *) &peeraddr,
				 sizeof(struct sockaddr_in)) < 0) {
			printf("sendto error!\n");
			exit(3);
		}
		printf("'%s' send ok\n", recmsg);
	}
#endif 
}
