import RPi.GPIO as GPIO
import serial
import socket
import threading
import time

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


def send(msg):
    s.send(msg.encode('utf-8'))
    
def revice():
    print("START")
    while True:
        conn,addr = s.accept()
        print(conn,addr)
        while True:
            try:
                data = conn.recv(1024)
                DIR = data.decode()
                if DIR[len(DIR)-1]!='0':
                    print(DIR)
                    conn.send(data.upper())
                    msgg = int(DIR[0])
                    length = len(bin(msgg))  
                    for k in range (length-2):    
                        if (int(bin(msgg)[length-(k+1):length-k],2) == 1):
                            GPIO.output(GPIO_output[k],GPIO.HIGH)
                        else:
                            GPIO.output(GPIO_output[k],GPIO.LOW)
                    for k in range (12-(length-2)):
                        GPIO.output(GPIO_output[k+(length-2)],GPIO.LOW)
                else:
                    print(0)
                    for k in range 12:    
                            GPIO.output(GPIO_output[k],GPIO.LOW)
                time.sleep(0.175)

            except ConnectionResetError as e:
                print('close ',addr,' connect！')
                break
        conn.close()

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
ip="192.168.1.4"
port = 30021
s.bind((ip,port))
s.listen(5)

if __name__=="__main__":
     thread2 = threading.Thread(target = revice)
     thread2.start()

