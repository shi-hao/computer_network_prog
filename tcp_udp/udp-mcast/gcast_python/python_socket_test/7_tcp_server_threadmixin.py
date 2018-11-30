from socketserver import ThreadingTCPServer, BaseRequestHandler, StreamRequestHandler

HOST = '10.80.5.232'
PORT = 7777

# class TcpRequestHandler(BaseRequestHandler):  # 定义request handler类，从BaseRequestHandler类继承
#
#     def handle(self):  # 复写handle()方法，注意：该方法必须复写，用于处理当前的request
#         self.data = self.request.recv(1024).strip()  # self.request是和客户端连接的套接字，可直接使用
#         print("{} wrote:".format(self.client_address[0]))
#         print(self.data)
#         self.request.sendall(self.data.upper())

class TcpRequestHandler(StreamRequestHandler):#最要注意的就是，用rfile接收数据，数据末尾要带\n，jmeter里要空行
    def handle(self):
        data = self.rfile.readline().strip()  # self.rfiel/wfile是对原始socket数据收发的封装，像读写文件一样方便。
        print("recevie data from : ", self.client_address)
        print("data:", data)
        self.wfile.write(data.upper())

#The difference is that the readline() call in the second handler will call recv() multiple times until it encounters a newline character, while the single recv() call in the first handler will just return what has been sent from the client in one sendall() call.

if __name__ == "__main__":
    server = ThreadingTCPServer((HOST, PORT), TcpRequestHandler)
    server.serve_forever()
