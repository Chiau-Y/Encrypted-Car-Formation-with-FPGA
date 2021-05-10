import RPi.GPIO as GPIO
import threading           
import socket 
import time 

GPIO.setmode(GPIO.BOARD)

GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(15,GPIO.OUT)
GPIO.setup(29,GPIO.OUT)
GPIO.setup(31,GPIO.OUT)
GPIO.setup(33,GPIO.OUT)
GPIO.setup(35,GPIO.OUT)
GPIO.setup(37,GPIO.OUT)
GPIO.setup(7,GPIO.OUT)
GPIO.setup(8,GPIO.OUT)
GPIO.setup(10,GPIO.OUT)
GPIO.setup(12,GPIO.OUT)
GPIO.setup(16,GPIO.OUT)
GPIO.setup(18,GPIO.OUT)
GPIO.setup(22,GPIO.OUT)
GPIO.setup(24,GPIO.OUT)
GPIO.setup(26,GPIO.OUT)
GPIO.setup(32,GPIO.OUT)
GPIO.setup(36,GPIO.OUT)
GPIO.setup(38,GPIO.OUT)
GPIO.setup(40,GPIO.OUT)
GPIO.setup(21,GPIO.OUT)
GPIO.output(21,GPIO.HIGH)
GPIO.setup(23,GPIO.OUT)
GPIO.output(23,GPIO.HIGH)
GPIO.setup(19,GPIO.IN)
GPIO_output = [8,10,12,16,18,22,24,26,32,36,38,40]

close=0




def send():
    global close
    while True:
        msg1 = input()
        if (msg1[0]=='p'):
            close=1
            break
        else:
            s.send(msg1.encode('utf-8'))
              
def revice():
    data = s.recv(1024)
    startflag = data.decode()  
    if startflag[0] == 's' :
        msg_p = 0
        GPIO.output(21,GPIO.HIGH)
        GPIO.output(23,GPIO.LOW)
        while True :
            data_2 = s.recv(1024)
            dataStr = data_2.decode()
            msg = dataStr.split(',')
            for l in range (4):
                print(msg[l])
                GPIO.output(21,GPIO.LOW)
                GPIO.output(23,GPIO.HIGH) 
                msgg = int(msg[l])
                length = len(bin(msgg))  
                for k in range (length-2):    
                    if (int(bin(msgg)[length-(k+1):length-k],2) == 1):
                        GPIO.output(GPIO_output[k],GPIO.HIGH)
                    else:
                        GPIO.output(GPIO_output[k],GPIO.LOW)
                    
                for k in range (12-(length-2)):
                    GPIO.output(GPIO_output[k+(length-2)],GPIO.LOW)
                GPIO.output(23,GPIO.LOW)
            while (GPIO.input(19) == 0) :
                pass
thread1 = threading.Thread(target = send)
thread2 = threading.Thread(target = revice)

s = socket.socket()  
ip="192.168.1.28" 
port = 35176
s.connect((ip, port))      

thread1.start()
thread2.start()