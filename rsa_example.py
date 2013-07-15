#!/usr/bin/python
import serial
import time
from RSA import *

privateKey = [14351, 1283]
publicKey = [14351, 11]

ser = serial.Serial("/dev/ttyUSB2", 115200)

received_string = ""
plain_enable = "enable"
plain_disable = "disable"
cipher = ""

while ser.inWaiting() == 0:
    pass

while ser.inWaiting() > 0:
    received_string += ser.read(1)

decrypt(received_string, privateKey)


cipher_enable = encrypt(plain_enable, publicKey)

for i in cipher_enable:
    ser.write(i)

time.sleep(10)

cipher_disable = encrypt(plain_disable, publicKey)
for j in cipher_disable:
    ser.write(j)
