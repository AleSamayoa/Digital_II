/* 
 * File:  usart.h
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación usart
 * Revision history: 
 */
#include <xc.h>
#include <stdint.h>
#include "USART.h"

void config_us(const uint32_t baudrate, const uint8_t BRGH) {
    if (BRGH == 0) {
        SPBRG = _XTAL_FREQ/(64*baudrate) - 1;
        TXSTAbits.BRGH = 0;
    } else {
        SPBRG = _XTAL_FREQ/(16*baudrate) - 1;
        TXSTAbits.BRGH = 1;
    }
    BAUDCTL = 0B00000000; 
    TXSTA = 0B00100100; 
    RCSTA = 0B10010000; 
    U_RX = 1;
    U_TX = 0;
}

void usart_char(const char t) {
    while (TXSTAbits.TRMT == 0);   
    TXREG = t;
    
}
void usart_string(const char *data, const uint8_t max) {
    int i=0;
    for (i=0 ; i<max && data[i]!='\0' ; i++) {
        usart_char(data[i]);
    }
    __delay_ms(30);
}

uint8_t Rusart() {
    return PIR1bits.RCIF;
}

char usart_readchar() {
    while (!Rusart());   // Wait for data to be available
    return RCREG;
}


uint8_t usart_readstring(char *b, uint8_t max) {
    uint8_t i = 0;
    char tmp = 1;
    for (i=0 ; i<max-1 ; i++) {
        tmp = usart_readchar();
        if (tmp == '\0' || tmp == '\n' || tmp == '\r') {
            break;
        }
        b[i] = tmp;
    }
    
    b[i+1] = '\0';
    
    return i;
}



