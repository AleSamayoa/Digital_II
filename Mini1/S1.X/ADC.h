/* 
 * File:  ADC.h  
 * Author: Ale Samayoa
 * Comments: Librer�a para el ADC
 * Revision history: 
 */
//Libreria ADC S1
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void valadc(volatile uint8_t *a);
void adcon(void);

#endif	/* XC_HEADER_TEMPLATE_H */