import socket
import time

T_PORT = 16543

TCP_IP = 'peer1'

BUF_SIZE = 1024

MSG = 'Hello karl'


def try_connect():

    # create a socket object name 'k'

    k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

    try:
        k.connect((TCP_IP, T_PORT))
    except: 
        print("peer1 not up")
    else:
        k.send(MSG.encode())
        print("message sent")
        #data = k.recv(BUF_SIZE).decode()
        #print(data)
    time.sleep(4)
    k.close


print("v1")



while True:
    try_connect()
    time.sleep(1)