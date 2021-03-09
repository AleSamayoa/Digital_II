/*
 * File:   PIC.c
 * Author: Ale Samayoa
 * Description: Función del pic
 * Created on 6 de marzo de 2021, 07:22 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"
#include "USART.h"
#include "GIRO.h"

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

#define _XTAL_FREQ 4000000

//**************************************************************
// Variables y prototipos de funciones
//**************************************************************
char input;
void Setup(void);

//******************************************************************************
//Loop principal 
//******************************************************************************
void main(void) {
    __delay_ms(500);
    Setup();    
    giro_init();  
    while (1) {
            giro_read(); 
    }
    return;
}


//**************************************************************
// Funciones 
//**************************************************************
void Setup(void) {
    //Configuración de puertos
    ANSEL = 0;
    TRISA = 0;
    PORTA = 0;
    // Configuración para interrupciones que encenderán las luces
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1; 
    return;

}
void __interrupt() int1(void) {
    //Se recibe el mensaje 1on/1off/2on/2off de la comunicación con la ESP32 
    //que se encienda o apague los leds 
    if (PIR1bits.RCIF) {
        input = RCREG;
        if (input == '1on') {
            PORTAbits.RA0 = 1;
        }
        if (input == '1off') {
            PORTAbits.RA0 = 0;
        }
        if (input == '2on') {
            PORTAbits.RA1 = 1;
        }
        if (input == '2off') {
            PORTAbits.RA1 = 0;
        }
    }
}


