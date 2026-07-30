# UART Driver — ATmega328P

Created a bare-metal UART communication driver in C for the ATmega328P 
microcontroller. Transmits and monitors data over a serial port through 
direct register configuration with no Arduino libraries. Output verified 
live in PuTTY terminal at 9600 baud.

## What This Demonstrates

- UART peripheral configuration via UBRR0, UCSR0B, UCSR0C registers
- Baud rate calculation and configuration (9600 baud at 16MHz)
- Polling-based transmit with UDRE0 status flag checking
- uart_send_byte() and uart_send_string() driver functions
- Live serial output verified in PuTTY terminal

## Why Bare-Metal UART

Arduino's Serial.println() hides the UART hardware completely. 
Writing directly to registers UBRR0, UCSR0B and UDR0 provides 
full control over timing, format and data flow. This is how 
serial communication is handled in production firmware.

## Build and Flash

make flash

Change PORT in Makefile to match your COM port.
Open PuTTY at 9600 baud on the same COM port to see output.

## Hardware

- Elegoo UNO R3 (ATmega328P at 16MHz)
- USB connection to PC for UART output

## Tools

- avr-gcc, avr-libc, avrdude (via MSYS2 on Windows)
- PuTTY serial terminal (9600 baud, COM3)
- ATmega328P datasheet Section 19 (USART0)
- GNU Make

