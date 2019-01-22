import socket

server_addr = ('10.80.5.232', 6666)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(server_addr)  # 服务端地址端口绑定
while True:
    data, client_addr = s.recvfrom(2048)  # 接收数据，获取客户端地址
    rdata = data.decode('utf-8')
    if rdata == 'f':
        print("get f.")
        s.sendto('close'.encode('utf-8'), client_addr)
        break
    print("receive client data: %s. from %s" % (rdata, client_addr))
    s.sendto('ok'.encode('utf-8'), client_addr)  # 回复请求。
s.close()
