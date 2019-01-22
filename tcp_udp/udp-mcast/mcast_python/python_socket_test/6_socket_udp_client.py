import socket

client_addr = ('10.80.5.232', 5555)  # 配置客户端ip和端口，让端口保持固定
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(client_addr) # 与socket绑定
while True:
    req = input("input request data : ")
    try:
        s.sendto(req.encode('utf-8'), ('10.80.5.232', 6666))
        resp = s.recv(1024)
        print(resp.decode('utf-8'))
    except socket.error as e:
        print(e)
s.close()
