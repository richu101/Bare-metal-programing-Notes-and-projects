import serial
ser =  serial.Serial('/dev/ttyUSB0')
print(ser.name)
a = int(input("enter a char to begin the game"))
ser.write(a)
ser.close()