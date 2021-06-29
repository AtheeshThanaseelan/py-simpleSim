import socket
import numpy

T_PORT = 16543
TCP_IP = '192.168.2.41'
BUF_SIZE = 1024



# create a socket object name 'k'
k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
k.bind((TCP_IP, T_PORT))
k.listen(1)
con, addr = k.accept()


print ('Connection Address is: ' , addr)
while True :
    print("looped")
    data = con.recv(BUF_SIZE)
    arr = numpy.frombuffer(data, dtype="float64")
    if not data:
        print("data")
        #break
    
    print ("Received data", data)
    print (arr)

    #con.send(data.encode())
    
    con.close()
    con, addr = k.accept()



con.close()