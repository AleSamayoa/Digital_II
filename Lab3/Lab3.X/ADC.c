#include <stdint.h> 
#include <pic16f887.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000}
void ADC_Init(void){
   TRISA = 0b00000011;
   ADCON1 = 0b10000000;
   ANSEL = 0b00000011;
   ADCON0 = 0b11000001;
   ADCON0 = 0b11000011;
   //hacer if para ver si adc go ya esta abajo y usar * para copiar la info
}

