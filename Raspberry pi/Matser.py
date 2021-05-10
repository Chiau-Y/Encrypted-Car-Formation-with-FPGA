import socket            
import threading
import time
close=0
a,e,p,q=900,35,37,53
n=p*q
# def send():
   # global close
   # while True:
       # msg = input()
       # if (msg[0]=='p'):
           # close=1
           # break
       # else:
           # con.send(msg.encode('utf-8'))

def send():
    global a,e,n
    startflag = input()   
    con.send(startflag.encode('utf-8'))
    while True:
        msgg=1
        for i in range(e):
            msgg=(msgg*a)%n
        msg=str(msgg)
        con.send(msg.encode('utf-8'))
        a=a+1
        time.sleep(0.175)
        
        if a == 1920:
            break

def revice():
    while True:
        data = con.recv(1024)
        print('revice:',data.decode())
        
thread1 = threading.Thread(target = send)
thread2 = threading.Thread(target = revice)

s = socket.socket()  
ip="192.168.1.13"     
port = 30179
#host = socket.gethostname()
#print(host)
s.bind((ip, port))      
s.listen(5)

con,addr = s.accept() 
print ('addr:', addr)

thread1.start()
thread2.start()

#time.sleep(5)
#s.close()
#print('close')
