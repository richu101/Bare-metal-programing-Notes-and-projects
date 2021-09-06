### To open serial com port

minicom -D /dev/ttyUSB0  -b 9600

* using pyserial module
python3 -m serial.tools.miniterm /dev/ttyUSB0 9600