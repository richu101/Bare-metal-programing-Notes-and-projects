
#Main application file name
MAIN_APP = main
#Main hex file path in windows format
MAIN_HEX_PATH = E:\Electronics\Bare-metal-programing-Notes-and-projects\$(MAIN_APP).hex

PROGRAMMER_TYPE = usbasp #or usbtiny
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
PROGRAMMER_ARGS = 	
# Compiler and other Section
CC = E:\Electronics\ARDUINO_IDE\arduino-1.8.16\hardware\tools\avr\bin\avr-gcc.exe
#   JCOPY = avr-objcopy
# avr-objcopy -oihex -R .eeprom blink.elf blink.hex
OBJCOPY = E:\Electronics\ARDUINO_IDE\arduino-1.8.16\hardware\tools\avr\bin\avr-objcopy.exe
AVRDUDE = E:\Electronics\avrdude\bin\avrdude.exe
MCU = atmega328p
CONFIG = E:\Electronics\avrdude\etc\avrdude.conf
#Options for avr-gcc
CFLAGS = -g -Os -o

#Linking options for avr-gcc

LFLAGS = -Os -mmcu=atmega328p -o

#Options for HEX file generation
HFLAGS =  -O ihex -R .eeprom
#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -C
DUDEFLAGS += E:\Electronics\avrdude\etc\avrdude.conf
DUDEFLAGS += -c
DUDEFLAGS += usbasp 
DUDEFLAGS += -p
DUDEFLAGS += m328p  
DUDEFLAGS += -P 
DUDEFLAGS += USBasp # add port of the isp programmer here
DUDEFLAGS += -b 
DUDEFLAGS += 19200 
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application 
SRC = $(MAIN_APP).c


# The headers files needed for building the application
INCLUDE = -I 
INCLUDE  += 

# commands Section


Burn : Build
	$(AVRDUDE) $(DUDEFLAGS) -v
Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@

LFUSE = 0x62
HFUSE = 0xdf
EFUSE = 0x00

## Generic 
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 

fuses: 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) 
	           $(PROGRAMMER_ARGS) $(FUSE_STRING) 
show_fuses:
	$(AVRDUDE)  -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) 	

## Called with no extra definitions, sets to defaults
set_default_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 
set_default_fuses:  fuses

## Set the fuse byte for full-speed mode with external crystal (8 Mhz and more)
## Note: can also be set in firmware for modern chips
set_external_fast_fuse: LFUSE = 0xFF
set_external_fast_fuse: HFUSE = 0xDE
set_external_fast_fuse: EFUSE = 0xFF
set_external_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m
set_external_fast_fuse: fuses

## Set the fuse byte for full-speed mode
## Note: can also be set in firmware for modern chips
set_fast_fuse: LFUSE = 0xE2
set_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m 
set_fast_fuse: fuses