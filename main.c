#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

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

uint16_t adc_read(uint8_t channel) {
    // Select ADC channel
    ADMUX = (1 << REFS0) | (channel & 0x0F);
    
    // Enable ADC and start conversion
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    return ADC;
}

int main(void) {
    uart_init(103);

    char buffer[16];
    uint16_t adc_value;

    while (1) {
        adc_value = adc_read(0);
        itoa(adc_value, buffer, 10);
        uart_send_string("ADC Value: ");
        uart_send_string(buffer);
        uart_send_string("\r\n");
        _delay_ms(100);
    }

    return 0;
}