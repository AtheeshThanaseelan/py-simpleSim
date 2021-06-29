import logging
import threading
import time
import socket

T_PORT_SERVER = 16543
T_PORT_CLIENT = 16544

if True:
    TCP_PEER_IP = '192.168.2.41'
    TCP_IP = '192.168.2.52'
else:
    TCP_IP = '192.168.2.41'
    TCP_PEER_IP = '192.168.2.52'

BUF_SIZE = 1024

format = "%(asctime)s: %(message)s"
logging.basicConfig(format=format, level=logging.INFO, datefmt="%H:%M:%S")

def tcp_listen(name):
    # create a socket object name 'k'
    k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
    k.bind((TCP_IP, T_PORT_SERVER))
    k.listen(1)
    con, addr = k.accept()
    logging.info("tcp_listen   : Connection Address is "+str(addr))
    while True :
        data = con.recv(BUF_SIZE).decode()
        if not data:
            pass
            #break
        
        logging.info("tcp_listen   : Received data "+ data)

        #con.send(data.encode())
        
        #con.shutdown()
        con.close()
        con, addr = k.accept()

    con.close()
    
    
    
def update_calc(name):

    while True:
    
        MSG = 'Hello karl'
        
        k = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
        #k.bind((TCP_IP, T_PORT_CLIENT))
        
        try:
            k.connect((TCP_PEER_IP, T_PORT_SERVER))
        except:
            logging.info("update_calc   : peer not available")
        else:
            k.send(MSG.encode())
            data = k.recv(BUF_SIZE).decode()
            log = "update_calc  Sent data to peer: " + data
            logging.info(log)
            #print(data)
        #k.shutdown()
        time.sleep(2)
    k.close
    




if __name__ == "__main__":

    
    logging.info("Main    : before creating tcp listen thread")
    tcplisten = threading.Thread(target=tcp_listen, args=(1,))
    logging.info("Main    : before running tcp listen thread")
    tcplisten.start()
    
    logging.info("Main    : before creating update thread")
    updatecalc = threading.Thread(target=update_calc, args=(1,))
    logging.info("Main    : before running update thread")
    updatecalc.start()   
    
    
    
    logging.info("Main    : wait for the thread to finish")
    
    
    # x.join()
    logging.info("Main    : all done")
    
    