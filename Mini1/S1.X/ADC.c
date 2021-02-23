/*
 * File:   ADC_lib.c
 * Author: Ale Samayoa
 */
//Libreria ADC S1
#include <stdint.h> 
#include <pic16f887.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000
//Para obtener los valores de ADC
#include <xc.h>
#include <stdint.h>
#include "ADC.h"

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
