
/* 
 * File: USART.h
 * Author: Ale Samayoa
 *Se utilizó y se adaptaron las librerías de Ligo George 
 *de la página www.electrosome.com
 *Enlace: https://electrosome.com/uart-pic-microcontroller-mplab-xc8/
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __USART_H_
#define	__USART_H_
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

char USART_In(const long int baudrate);
void Wr_USART(uint8_t a);
void Wr_USART_String(char *a);
char UART_In(const long int baudrate);
uint8_t Rd_USART(void);
void Rd_USART_String(char *Output, unsigned int length);
#endif	/* 	__USART_H_ */





