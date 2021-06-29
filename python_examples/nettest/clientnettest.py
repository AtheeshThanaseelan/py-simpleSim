import socket

T_PORT = 16543

TCP_IP = '192.168.2.41'

BUF_SIZE = 1024

MSG = 'Hello karl'

# create a socket object name 'k'

k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

k.connect((TCP_IP, T_PORT))

k.send(MSG.encode())

data = k.recv(BUF_SIZE).decode()
print(data)

k.close