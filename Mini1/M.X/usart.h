/* 
 * File:  usart.h
 * Author: Ale Samayoa
 * Comments: Librería para la comunicación usart
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void config_us(void);
void tvirt_usart(char t);
void tnl_usart(void);
void erase_usart(void);
void Rusart(uint8_t *r);
void n_ascii(uint8_t value, char *code);
void usart_string(char *data);

#endif	/* XC_HEADER_TEMPLATE_H */


