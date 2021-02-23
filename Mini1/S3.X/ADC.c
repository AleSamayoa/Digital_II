/*
 * File:   ADC.c
 * Author: Ale Samayoa
 */
//Libreria ADC S3

#include <xc.h>
#include <stdint.h>
#include "adc.h"

#define _XTAL_FREQ 4000000  

void valadc(volatile uint8_t *a) { 
    *a = ADRESH;
}

void adcon(void) {
    if (0 == ADCON0bits.GO_nDONE) {
        __delay_ms(5); 
        ADCON0bits.GO_nDONE = 1;
    }
}
