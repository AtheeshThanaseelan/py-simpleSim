import socket
import numpy
import debugview
from pynput import keyboard
import threading
import time
import math


T_PORT = 16543
TCP_IP = '127.0.0.1'
BUF_SIZE = 1024

quit = False




# create a socket object name 'k'
k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
k.bind((TCP_IP, T_PORT))
k.listen(1)
con, addr = k.accept()


print ('Connection Address is: ' , addr)

v = debugview.debugview()


while (not(quit)) :
    data = con.recv(BUF_SIZE)
    arr = numpy.frombuffer(data, dtype="float64")
    if not data:
        print("not data")

    sub_line = []
    for x in range(0,len(arr)):
        sub_line.append(arr[x])
        if ((x+1)/6 == math.ceil((x+1)/6)):
            v.addline(sub_line)
            sub_line = []

    v.update()
    
    con.close()
    con, addr = k.accept()

con.close()
