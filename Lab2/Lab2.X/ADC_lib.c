/*
 * File:   ADC_lib.c
 * Author: Ale Samayoa
 */



#include <stdint.h> 
#include <pic16f887.h>
#include "ADC_lib.h"
#define _XTAL_FREQ 8000000
//Para obtener los valores de ADC
void valADC(uint8_t a) {
    INTCON  = 0b11101000; 
    PIR1bits.ADIF   = 0;   
    PIE1bits.ADIE   = 1;   
    ADCON1bits.ADFM = 0;   
    if (a == 1){
        __delay_us(10);
        a = 0;
        ADCON0bits.GO = 1;
    }
}

