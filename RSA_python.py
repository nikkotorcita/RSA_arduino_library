#!/usr/bin/python
import serial

ser = serial.Serial("/dev/ttyUSB0", 115200)

print "hello!"

out = ""

while ser.inWaiting() == 0:
    print "waiting"
while ser.inWaiting() > 0:
    out = ser.read(1)
    print out
print "done 1"

