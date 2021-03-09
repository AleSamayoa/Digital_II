/* 
 * File:  usart.h
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación usart
 * Revision history: 
 */


#ifndef USART_H
#define	USART_H
#define _XTAL_FREQ  4000000
#define U_RX     TRISCbits.TRISC7
#define U_TX     TRISCbits.TRISC6
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


void config_us(const uint32_t baudrate, const uint8_t BRGH);
void usart_char(const char t);
void usart_string(const char *data, const uint8_t max);
uint8_t Rusart();
char usart_readchar();
uint8_t usart_readstring(char *b, uint8_t max);



#endif	/* XC_HEADER_TEMPLATE_H */


