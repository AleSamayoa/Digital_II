/* 
 * File:  usart.h
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación usart
 * Revision history: 
 */
#include <xc.h>
#include <stdint.h>
#include "usart.h"

#define _XTAL_FREQ 8000000

void config_us(void) {
    SPBRG = 25; 
    SPBRGH = 0;
    BAUDCTL = 0B00000000; 
    TXSTA = 0B00100100; 
    RCSTA = 0B10010000; 
}

void tvirt_usart(char t) {
    if (1 == TXSTAbits.TRMT) {
        TXREG = t;
    }
}

void tnl_usart(void) {
    if (1 == TXSTAbits.TRMT) {
        TXREG = 13;
    }
}

void erase_usart(void) {
    if (1 == TXSTAbits.TRMT) {
        TXREG = 12;
    }
}

void Rusart(uint8_t *r) {
    if (1 == PIR1bits.RCIF) {
        *r = RCREG;
    }
}

void n_ascii(uint8_t value, char *code) {
    switch (value) {
        case 0:
            *code = 48;
            break;
        case 1:
            *code = 49;
            break;
        case 2:
            *code = 50;
            break;
        case 3:
            *code = 51;
            break;
        case 4:
            *code = 52;
            break;
        case 5:
            *code = 53;
            break;
        case 6:
            *code = 54;
            break;
        case 7:
            *code = 55;
            break;
        case 8:
            *code = 56;
            break;
        case 9:
            *code = 57;
            break;
        default:
            *code = 63;
            break;
    }
}

void usart_string(char *data) {
    int i;
    for (i = 0; data[i] != '\0'; i++)
        tvirt_usart(data[i]); 
    __delay_ms(30);
}
