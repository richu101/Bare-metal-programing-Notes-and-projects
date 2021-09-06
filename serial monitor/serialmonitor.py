import serial
ser =  serial.Serial('/dev/ttyUSB0')
print(ser.name)
while 1:
    a = input("enter a char to begin the game")
    ser.write(a)
    if a == 'q':
        exit()
ser.close()