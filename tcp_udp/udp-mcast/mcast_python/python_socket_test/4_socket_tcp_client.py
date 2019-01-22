import socket, time

HOST = '192.168.149.223'
PORT = 8804

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 1次连接多次数据。
# s.connect((HOST, PORT))
# for i in range(10):
#     data = 'socket tcp test.' + str(i)
#     s.sendall(data.encode("utf-8"))
#     resp = s.recv(1024)
#     print("response:", resp.decode('utf-8'))
#     time.sleep(1)
# s.sendall('f'.encode("utf-8"))
# s.close()

# 连接1次，发1次。
s.connect((HOST, PORT))
data = '(alarmdata|140802033|101| |2)'
s.sendall(data.encode("utf-8"))
# s.sendto(data.encode("utf-8"),(HOST, PORT))
resp = s.recv(1024)
print("response:", resp.decode('utf-8'))
time.sleep(1)
s.close()
