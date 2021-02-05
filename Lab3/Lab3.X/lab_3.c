/*
 * File:   lab_3.c
 * Author: Ale Samayoa
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Created on 31 de enero de 2020, 11:20 AM
 */

#include <xc.h>
//******************************************************************************
// CONFIGURACION
//******************************************************************************
// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

//Definimos los pines según como los tengo en proteus
#define _XTAL_FREQ 8000000
#define RS RE0
#define EN RE1
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include "LCD.h"
//******************************************************************************
// Variables
//******************************************************************************

uint8_t contador; //para el contador que se va a poner con la USART


//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
void inc(void);
void rest(void);
void conversion(void);

//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {

    setup();
    

    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {
        inc();
        rest();
        

       
             
    }

 }

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    //configurar para interrupciones
    di();
    ei();
    //Configuracion del ADC
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=0;
    ADCON0bits.ADON=1;
    //En esencia usamos Portd para la LCD, E para habilitar la LCD y el reset y el port A para los pots
    TRISE = 0;
    PORTE = 0;
    TRISA = 0;
    PORTA = 0;
    ANSEL = 0; //Port A a analog
    ANSELH = 0;
    TRISD = 0;
    PORTD = 0;
}


//******************************************************************************
// Funciones
//******************************************************************************

    void inc(){
        if (PORTBbits.RB0==1)
        contador ++;
    }
    //buscar funcion que lo resta pero hacer lo mismo con rb1
    void rest(){
        if (PORTBbits.RB1==1);
        contador --;
        
    }
    void conversion(){
    
    }

//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() int1(void){
    //la configuracion para la interrupcion, en esto realizar antirebote
    if (INTCONbits.T0IF == 1){}
    //antirebote?
    INTCONbits.T0IF=0;
    if (PIR1bits.ADIF==1){}
    PIR1bits.ADIF=0;
    
}


