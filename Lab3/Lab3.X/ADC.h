/* 
 * File:   ADC.h
 * Author: Ale Samayoa
 * Comments:
 * Revision history: 
 */

#ifndef __ADC_h_
#define __ADC_h_

#include <xc.h>
#include <stdint.h>

void ADC_Init(void);
uint8_t ADCval(uint8_t x);
#endif	/* __ADC_h_ */



