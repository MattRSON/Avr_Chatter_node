#include <avr/io.h>

#define BAUD 57600
#define UBRR_VAL ((F_CPU / (16UL * BAUD))-1)


// Initialize the UART
void avr_uart_init(void)
{
    // Enable bidirectional UART

    UCSRB |= (1<<RXEN)|(1<<TXEN);
    //Use 8-bit characters | set mode: 8 data bits, no parity, 1 stop bit
    UCSRC |= (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
    // Set the Baud rate
    UBRRH = (UBRR_VAL >> 8);
    UBRRL = UBRR_VAL;
}

// Send one char (blocking)
void avr_uart_send_byte(uint8_t tx_byte)
{
    // Wait to be able to transmit
    while((UCSRA & (1<<UDRE)) == 0)
        asm volatile("nop"::);
    // Put the data into the send buffer
    UDR = tx_byte;
}

// Get one char if available, otherwise -1
int16_t avr_uart_receive_byte(void)
{
    if(!(UCSRA & (1<<RXC)))
    {
        return UDR;
    }
    else
    {
        return -1;
    }
}
