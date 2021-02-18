/*
 * File:   s1.c
 * Author: Ale Samayoa
 * Description: Función del segundo pic, s1
 * Created on 12 de febrero de 2021, 09:08 AM
 */
/* Diseñe e implemente una rutina en donde utilice el ADC para obtener el 
 * valor del divisor de voltaje utilizando un potenciómetro.
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <stdint.h>
#include "ADC.h"

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000


//******************************************************************************
// Variables
//******************************************************************************
char a=1;
char v;


//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {

    setup();
    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {
        
        valADC(a);
        
       
    }
}

 

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {

    ANSELH = 0;
    ANSEL = 0b00000001;
    TRISA = 0b00000001;
    ADCON0 = 0b01010101;
    
    //timer 0
    OPTION_REG  = 0x84;
    TMR0        = 100;
    INTCON      = 0b11101000;
}



//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() int1(void){
    //la configuracion para la interrupcion,
    INTCON  = 0b11101000; 
    IOCB = 0b00000011;
    if (PIR1bits.ADIF == 1){
           a=1;
           v= ADRESH;
           
           PIR1bits.ADIF = 0;
       }
       
}