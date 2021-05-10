import serial
import threading           
import socket 
import time 

COM_PORT = "COM9"  # 請自行修改序列埠名稱
BAUD_RATES = 9600
data_arduino = serial.Serial(COM_PORT, BAUD_RATES)

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
        GPIO.output(21,GPIO.HIGH)
        GPIO.output(23,GPIO.LOW)
        while True :
            data_2 = s.recv(1024)
            dataStr = data_2.decode()
            msg = dataStr.split(',')
            data_arduino.write(msg.encode() + b"\n")
            
            # for l in range (4):
            #     data_arduino.write(msg[l].encode() + b"\n")
            # while (GPIO.input(19) == 0) :
            #     pass

thread1 = threading.Thread(target = send)
thread2 = threading.Thread(target = revice)

s = socket.socket()  
ip="192.168.1.28" 
port = 35176
s.connect((ip, port))      

thread1.start()
thread2.start()