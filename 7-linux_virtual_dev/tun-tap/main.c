#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/if_tun.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int tun_alloc(int flags)
{
	struct ifreq ifr;
	int fd, err;
	char *clonedev;

	clonedev = "/dev/net/tun";
	if ((fd = open(clonedev, O_RDWR)) < 0) {
		printf("open dev failed\n");
		return fd;
	}
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = flags;
	if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
		close(fd);
		return err;
	}
	printf("Open tun/tap device: %s for reading...\n", ifr.ifr_name);
	return fd;
}


#define offset 12
//ip包头从第13个字节开始是源ip地址，从第17字节开始是目的ip地址
//校验和是第11和12字节
int data_proc(unsigned char* data, int size){
	unsigned int checksum=0;
	unsigned short tmp=0;
	printf("\n");
	for(int i=0;i<size;i++){
		printf("%d ", *(data+i));
	}
	printf("\n");

	//check sum
	*(data + 10) = 0;
	*(data + 11) = 0;

	//source
	*(data + 12) = 192;
	*(data + 13) = 168;
	*(data + 14) = 11;
	*(data + 15) = 20;

	//dest
	*(data + 16) = 192;
	*(data + 17) = 168;
	*(data + 18) = 0;
	*(data + 19) = 1;

	for(int i=0;i<20;i+=2)
		checksum+=*(unsigned short*)(data+i);
	checksum += (checksum>>16);
	checksum = ~checksum;

	//check sum
	*(data + 10) = checksum >> 8;
	*(data + 11) = checksum ;
}

int main(int argc, char* argv[])
{
	int tun_fd, nread;
	char buffer[1500];
	/* Flags: IFF_TUN
	   - TUN device (no Ethernet headers)
	 *
	 IFF_TAP
	 - TAP device
	 *
	 IFF_NO_PI - Do not provide packet information
	 */
	int isTun=0;
	if(argc >= 2)
		isTun = strcmp("tun", argv[1]);

	if(isTun == 0)
	{
		tun_fd = tun_alloc(IFF_TUN | IFF_NO_PI);
		printf("create tun device\n");
	}else{
		tun_fd = tun_alloc(IFF_TAP);
		printf("create tap device\n");
	}

	if (tun_fd < 0) {
		perror("Allocating interface");
		exit(1);
	}
	while (1) {
		nread = read(tun_fd, buffer, sizeof(buffer));
		if (nread < 0) {
			perror("Reading from interface");
			close(tun_fd);
			exit(1);
		}
		data_proc(buffer, nread);
		nread = write(tun_fd, buffer, nread);

		printf("Read %d bytes from tun/tap device\n", nread);
	}
	return 0;
}
