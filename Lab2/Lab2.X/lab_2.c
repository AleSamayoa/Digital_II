/*
 * File:   lab_2.c
 * Author: Ale Samayoa
 *
 * Created on 28 de enero de 2021, 10:22 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <stdint.h>
#include "ADC_lib.h"

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
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

//******************************************************************************
// Variables
//******************************************************************************

uint8_t contador; //para el contador 
//Variable que incrementa con el boton


//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
void counter(void);
void inc(void);
void rest(void);


//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {

    setup();
    
    

    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {
        //switch case? para encender los 7 segmentos
        counter();
        if (PORTBbits.RB0==1){
            inc();
        }
        
        if (PORTBbits.RB1==1){       
            rest();
        }
       
    }

 }

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    //configurar para interrupciones
    di();
    ei();
    //ver configuracion para adc
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=0;
    
    TRISE = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
}


//******************************************************************************
// Funciones
//******************************************************************************
void inc(void){
    contador ++;
}
void rest(void){
    contador --;
 }
void counter(void){
   switch (contador){
        case 0:
            PORTD= 0;
            RD0 = 1;
            __delay_ms(100);
            break;
        case 1:
            PORTD= 0;
            RD1 = 1;
            __delay_ms(100);
            break;
        case 2:
            PORTD= 0;
            RD2 = 1;
            __delay_ms(100);
            break;
       case 3:    
            PORTD= 0;
            RD3 = 1;
            __delay_ms(100);
            break;
        case 4:
            PORTD= 0;
            RD4 = 1;
            __delay_ms(100);
            break;
        case 5:
            PORTD= 0;
            RD5 = 1;
            __delay_ms(100);
            break;
        case 6:
            PORTD= 0;
            RD6 = 1;
            __delay_ms(100);
            break;
        case 7:
            PORTD= 0;
            RD7 = 1;
            __delay_ms(100);
            break;
        default:
            PORTD= 0;
            break;             
         
    }
}

//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() int1(void){
    //la configuracion para la interrupcion, en esto realizar antirebote
    if (INTCONbits.T0IF == 1){
        
        
    }
    //antirebote?
    INTCONbits.T0IF=0;
    if (PIR1bits.ADIF==1){}
    PIR1bits.ADIF=0;
    
}
