/*
 * File:   lab_1.c
 * Author: Ale Samayoa
 *
 * Created on 22 de enero de 2021, 08:13 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

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

char counter = 0; //para el semaforo, un contador que incremente
char player1 = 0; //para cada jugador, que vaya incrementando cuando se presiona
char player2 = 0;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
void semaforo(void);
void juego1(void);
void juego2(void);
void ganador(void);
//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {

    setup();

    //**************************************************************************
    // Loop principal
    //**************************************************************************

    while (1) {

        if (PORTBbits.RB0 == 1)
            semaforo();
        if (PORTBbits.RB1 == 1)
            juego1();
        if (PORTBbits.RB2 == 1)
            juego2 ();
        if (1)
            ganador();
             
    }

   

}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    TRISE = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b00000111;
    PORTB = 0;
    TRISC = 0;
    PORTC = 0;
}

//******************************************************************************
// Funciones
//******************************************************************************

void semaforo(void) {
    PORTE = 0; //clear all porque si
    PORTEbits.RE2 = 1; //rojo
    __delay_ms(500);
    PORTEbits.RE2 = 0;
    PORTEbits.RE1= 1; // se apaga rojo y se enciende amarillo
    __delay_ms(500);
    PORTEbits.RE1 = 0; // se apaga amarillo y se enciende verde
    PORTEbits.RE0 = 1;

}
void juego1 (void){
    player1 ++; //le sumamos uno a la variable del jugador 1
    switch (player1){ //no sabía como hacer esto así que con switch case se hizo
        case 0:
            PORTC = 0;
            PORTCbits.RC0 = 1;
            break;
        case 1:
            PORTC = 0;
            PORTCbits.RC1 = 1;
            break;
        case 2:
            PORTC = 0;
            PORTCbits.RC2 = 1;
            break;
        case 3:
            PORTC = 0;
            PORTCbits.RC3 = 1;
            break;
        case 4:
            PORTC = 0;
            PORTCbits.RC4 = 1;
            break;
        case 5:
            PORTC = 0;
            PORTCbits.RC5 = 1;
            break;
        case 6:
            PORTC = 0;
            PORTCbits.RC6 = 1;
            break;
        case 7:
            PORTC = 0;
            PORTCbits.RC7 = 1;
            break;
        default:
            PORTC= 0;
            break;             
         
    }
}
void juego2(void){
    player2 ++; //le sumamos uno a la variable del jugador 2
    switch (player2){
        case 0:
            PORTD = 0;
            PORTDbits.RD0 = 1;
            break;
        case 1:
            PORTD = 0;
            PORTDbits.RD1 = 1;
            break;
        case 2:
            PORTD = 0;
            PORTDbits.RD2 = 1;
            break;
        case 3:
            PORTD = 0;
            PORTDbits.RD3 = 1;
            break;
        case 4:
            PORTD = 0;
            PORTDbits.RD4 = 1;
            break;
        case 5:
            PORTD = 0;
            PORTDbits.RD5 = 1;
            break;
        case 6:
            PORTD = 0;
            PORTDbits.RD6 = 1;
            break;
        case 7:
            PORTD = 0;
            PORTDbits.RD7 = 1;
            break;
        default:
            PORTD= 0;
            break;             
         
    }
}
void ganador(void){
    if (PORTCbits.RC7 == 1)
        PORTAbits.RA0 = 1;
    if (PORTDbits.RD7 == 1)
        PORTAbits.RA1 = 1;
            
}