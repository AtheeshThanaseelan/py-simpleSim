import physicsEnv
import math
import socket
import time
import numpy

T_PORT = 16543
TCP_IP = '192.168.2.41'
BUF_SIZE = 1024

def serve_gfx(data):

    #data = [[1,1,1],[1,1,1],[2,2,2]]
    #data = [1,1,1]
    # create a socket object name 'k'

    k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

    try:
        k.connect((TCP_IP, T_PORT))
    except: 
        print("peer1 not up")
    else:
        k.send(data.tobytes())
        print("message sent")
        #data = k.recv(BUF_SIZE).decode()
        #print(data)
    time.sleep(4)
    k.close





if __name__ == "__main__":
    #g = physicsEnv.irr_btDebug(True)
    exp = physicsEnv.export_btDebug()
    w = physicsEnv.host(exp)
    w.addObject(1)
    o = w.getObject(0)

    for x in range(10):
        #print(o.getTransform_qat())
        w.update()        
        lst = exp.getLines()
        print(lst)
        arr = numpy.asarray(lst)
        print(arr.dtype)
        serve_gfx(arr)
        exp.update()