#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 255
/*********************************************************************
 *filename: mcastclient.c
 *purpose: ��ʾ�鲥��̵Ļ������裬��ʵ�����һ��������UDP�ͻ��˳���
 *tidied by: zhoulifa(zhoulifa@163.com) ������(http://zhoulifa.bokee.com)
 Linux������ Linux֪ʶ������ SOHO�� ������ ���ó�C����
 *date time:2007-01-25 13:10:00
 *Note: �κ��˿������⸴�ƴ��벢������Щ�ĵ�����Ȼ���������ҵ��;
 * ������ѭGPL
 *Thanks to: Google.com
 *Hope:ϣ��Խ��Խ����˹����Լ���������Ϊ��ѧ������չ����
 * �Ƽ�վ�ھ��˵ļ���Ͻ������죡��л�п�Դǰ���Ĺ��ף�
 *********************************************************************/
int main(int argc, char **argv)
{
	struct sockaddr_in peeraddr, myaddr;

	int sockfd;
	char recmsg[BUFLEN + 1];
	unsigned int socklen, n;

	/* ���� socket ����UDPͨѶ */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("socket creating error\n");
		exit(1);
	}
	socklen = sizeof(struct sockaddr_in);

	/* ���öԷ��Ķ˿ں�IP��Ϣ */
	memset(&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	if (argv[2])
		peeraddr.sin_port = htons(atoi(argv[2]));
	else
		peeraddr.sin_port = htons(7838);
	if (argv[1]) {
		/* ע���������õĶԷ���ַ��ָ�鲥��ַ�������ǶԷ���ʵ��IP��ַ */
		if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0) {
			printf("wrong group address!\n");
			exit(0);
		}
	} else {
		printf("no group address!\n");
		exit(0);
	}


#if 0
	/* �����Լ��Ķ˿ں�IP��Ϣ */
	memset(&myaddr, 0, socklen);
	myaddr.sin_family = AF_INET;
	if (argv[4])
		myaddr.sin_port = htons(atoi(argv[4]));
	else
		myaddr.sin_port = htons(23456);

	if (argv[3]) {
		if (inet_pton(AF_INET, argv[3], &myaddr.sin_addr) <= 0) {
			printf("self ip address error!\n");
			exit(0);
		}
	} else
		myaddr.sin_addr.s_addr = INADDR_ANY;

	/* ���Լ��Ķ˿ں�IP��Ϣ��socket�� */
	if (bind
			(sockfd, (struct sockaddr *) &myaddr,
			 sizeof(struct sockaddr_in)) == -1) {
		printf("Bind error\n");
		exit(0);
	}
#endif 

#if 1
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
#else 
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
#endif 

}
