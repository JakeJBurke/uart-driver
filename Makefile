MCU = atmega328p
F_CPU = 16000000UL
PORT = COM3

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

all: main.hex

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

main.elf: main.o
	$(CC) -mmcu=$(MCU) -o main.elf main.o

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

flash: main.hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b 115200 -U flash:w:main.hex:i

clean:
	rm -f main.o main.elf main.hex