import serial
import struct


ser = serial.Serial(port='/dev/cu.usbmodem14201', baudrate=9600) 


value1 = 40.73
value2 = 43.72 

data1 = bytearray(struct.pack("f",value1))
data2 = bytearray(struct.pack("f",value2))

while True:
    for i in data1:
        ser.write(bytes([i]))
    for j in data2:
        ser.write(bytes([j]))
    ser.write(bytes('H','utf-8'))
        
        