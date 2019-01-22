import socket, time, random
HOST = '10.80.5.232'
PORT = 7777
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))  # 绑定服务ip和端口
s.listen(1)  # 打开监听,数字大概就是表示可等待长度。
i = 0

# conn, addr = s.accept()
# print("client connected :", addr)
# while True:
#     data = conn.recv(1024)
#     if data.decode('utf-8') == 'f':
#         print("get f")
#         break
#     print("get client data :　", data.decode('utf-8'))
#     conn.sendall((str(i) + "(ok)").encode("utf-8"))
#     i += 1
# conn.close()  # 1次连接，多次数据，等待client端发来断开消息。


while True:  # 配合lr脚本
    conn, addr = s.accept()
    print("client connected :", addr)
    data = conn.recv(1024)
    if data.decode('utf-8') == 'f':
        break
    think_time = random.randint(0, 10)
    print("get client data :　%s ,wait for %d ss" % (data.decode('utf-8'), think_time))

    time.sleep(think_time)
    time.sleep(10)
    conn.sendall((str(i) + "(ok)").encode("utf-8"))
    i += 1
    print(i)
    conn.close()  # 1次连接1次数据
