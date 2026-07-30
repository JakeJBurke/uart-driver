#include <avr/io.h>
#include <util/delay.h>

void uart_init(unsigned int baud) {
    UBRR0H = (unsigned char)(baud >> 8);
    UBRR0L = (unsigned char)(baud);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_byte(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_send_string(const char* str) {
    while (*str) {
        uart_send_byte(*str);
        str++;
    }
}

int main(void) {
    uart_init(103);

    while (1) {
        uart_send_string("Hello from ATmega328P!\r\n");
        _delay_ms(1000);
    }

    return 0;
}