/*
 * File:   s2.c
 * Author: Ale Samayoa
 * Description: Función del tercer pic, s2
 * Created on 12 de febrero de 2021, 09:09 AM
 */
/* Diseñe e implemente una rutina para un microcontrolador utilizando
 * dos botones pueda incrementar y decrementar un contador de 8 bits.
 */


#include <xc.h>
#include <stdint.h>
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7


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

char contador = 0; //para el contador 

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
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
        
       PORTD = contador;
    }
    }

 

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    TRISE = 0;
    PORTE = 0;
    ANSELH = 0;
    ANSEL = 0b00000001;
    TRISA = 0b00000001;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    ADCON0 = 0b01010101;
    
    //timer 0
    OPTION_REG  = 0x84;
    TMR0        = 100;
    INTCON      = 0b11101000;
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
//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() int1(void){
    //la configuracion para la interrupcion,
    INTCON  = 0b11101000; 
    IOCB = 0b00000011;
    if (INTCONbits.RBIF == 1 && INTCONbits.RBIE == 1){
           if (PORTBbits.RB0 == 1){
               inc();
           }           
           if (PORTBbits.RB1 == 1){
               rest();
           }
    INTCONbits.RBIF = 0;
    }  
}

