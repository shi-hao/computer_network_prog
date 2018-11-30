import time
import struct
from socket import *

# 发送端本机ip和端口
SENDERIP = '10.8.0.1'
SENDERPORT = 1501

# 组播地址端口等
MYPORT = 1600
MYGROUP = '224.1.1.10'
MYTTL = 255


def sender():
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)

    s.bind((SENDERIP, SENDERPORT))  # 这句注释掉都可以。发送端口会被自动分配。
    # Set Time-to-live (optional)
    ttl_bin = struct.pack('@i', MYTTL)
    s.setsockopt(IPPROTO_IP, IP_MULTICAST_TTL, ttl_bin)
    status = s.setsockopt(IPPROTO_IP,
                          IP_ADD_MEMBERSHIP,
                          inet_aton(MYGROUP) + inet_aton(SENDERIP))  # 加入组播组
    while True:
        data = (time.strftime('%Y-%m-%d %H:%M:%S') + ': multicast test data.').encode('utf-8')  # socket发送需转成byte字节。
        s.sendto(data, (MYGROUP, MYPORT))
        print(data)
        print("send data ok !")
        #time.sleep(1)


if __name__ == "__main__":
    sender()
