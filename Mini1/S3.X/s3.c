/*
 * File:   s3.c
 * Author: Ale Samayoa
 * Description: Función del cuarto pic, s3
 * Created on 12 de febrero de 2021, 09:09 AM
 */
/* Diseñe e implemente una rutina para un microcontrolador en el cual utilice el
 *sensor de temperatura LM35. Adicionalmente ponga un semáforo dependiendo
 *del valor de temperatura según los siguientes rangos: t<25 verde, 25<t<36 amarillo,
 * y  t>36 rojo
 */
#include <xc.h>
#include <stdint.h>
#include "adc.h"

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

//******************************************************************************
//                          Funciones
//******************************************************************************

#define _XTAL_FREQ 8000000  

void setup(void);
void semaforo(void);
char a=1;
char v;
//******************************************************************************
//Loop principal 
//******************************************************************************

void main(void) {
    setup();
    while (1) {
        valADC(a);
        semaforo();
    }
}

//******************************************************************************
//Funciones
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
void semaforo (void){
   while (1) {
        if (v < 80){
            PORTD = 0b00000001;
        }
        else if(v >= 80 && v <= 91){
            PORTD = 0b00000010;
        }
        else {
            PORTD = 0b00000100;
        }
}
}
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

