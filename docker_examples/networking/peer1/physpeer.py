import socket

print("peer1 started")

T_PORT = 16543
TCP_IP = 'peer1'
BUF_SIZE = 30


# create a socket object name 'k'
k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
print("peer1 made socket")
k.bind((TCP_IP, T_PORT))
print("peer1 binded")
k.listen(1)
con, addr = k.accept()


print ('Connection Address is: ' , addr)
while True :
    print("looped")
    data = con.recv(BUF_SIZE).decode()
    if not data:
        print("data")
        #break
    
    print ("Received data", data)

    #con.send(data.encode())
    
    con.close()
    print("closed")
    k.listen(1)
    print("listenin")
    con, addr = k.accept()

print("goodbye")

con.close()