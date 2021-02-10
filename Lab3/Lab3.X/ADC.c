#include <stdint.h> 
#include <pic16f887.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000

void ADC_Init(void){
   TRISA = 0b00000011;
   ADCON1 = 0b10000000;
   ANSEL = 0b00000011;
   ADCON0 = 0b11000001;
   ADCON0bits.ADCS = 1;
}

uint8_t ADCval (uint8_t x){
    switch (x){
        case 0: TRISAbits.TRISA0 = 1; ANSELbits.ANS0 = 1; ADCON0bits.CHS = 0;   break;
        case 1: TRISAbits.TRISA1 = 1; ANSELbits.ANS1 = 1; ADCON0bits.CHS = 1;   break;
        case 2: TRISAbits.TRISA2 = 1; ANSELbits.ANS2 = 1; ADCON0bits.CHS = 2;   break;
        case 3: TRISAbits.TRISA3 = 1; ANSELbits.ANS3 = 1; ADCON0bits.CHS = 3;   break;
        case 4: TRISAbits.TRISA5 = 1; ANSELbits.ANS4 = 1; ADCON0bits.CHS = 4;   break;
        case 5: TRISEbits.TRISE0 = 1; ANSELbits.ANS5 = 1; ADCON0bits.CHS = 5;   break;
        case 6: TRISEbits.TRISE1 = 1; ANSELbits.ANS6 = 1; ADCON0bits.CHS = 6;   break;
        case 7: TRISEbits.TRISE3 = 1; ANSELbits.ANS7 = 1; ADCON0bits.CHS = 7;   break;
        case 8: TRISDbits.TRISD2 = 1; ANSELHbits.ANS8 = 1; ADCON0bits.CHS = 8;   break;
        case 9: TRISDbits.TRISD3 = 1; ANSELHbits.ANS9 = 1; ADCON0bits.CHS = 9;   break;
        case 10: TRISDbits.TRISD1 = 1; ANSELHbits.ANS10 = 1; ADCON0bits.CHS = 10;  break;
        case 11: TRISDbits.TRISD4 = 1; ANSELHbits.ANS11= 1; ADCON0bits.CHS = 11;  break;
        case 12: TRISDbits.TRISD0 = 1; ANSELHbits.ANS12 = 1; ADCON0bits.CHS = 12;  break;
        case 13: TRISDbits.TRISD5 = 1; ANSELHbits.ANS13 = 1; ADCON0bits.CHS = 13;  break;
        default: return 0;
    }
    ADCON0bits.ADON = 1;
    __delay_us(20);
    ADCON0bits.GO = 1;
    res:
    if   (ADCON0bits.GO_DONE ==1){goto res;}
    else {ADCON0bits.ADON=0; return ADRESH;}
    
}
