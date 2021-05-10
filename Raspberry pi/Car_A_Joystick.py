import serial
from time import sleep

data_arduino = serial.Serial('/dev/ttyACM0', 9600,timeout=1)
print("START")

while True:
	DIR = input('The Direction is: ')
	data_arduino.write(DIR.encode() + b"\n")
	print(DIR)