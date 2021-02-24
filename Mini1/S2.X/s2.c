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

#define _XTAL_FREQ 8000000            //8 MHZ
#define B0 RB0
#define B1 RB1
//-----------------------------------------------------------------------------
//Variables y prototipos de funciones
//-----------------------------------------------------------------------------
void Setup (void);
void __interrupt()int1(void); 
char  contador = 0;
uint8_t spidatos =0;

//-----------------------------------------------------------------------------
//Funciones
//-----------------------------------------------------------------------------
void Setup(void){
    //Configuración de puertos
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISD = 0;
    PORTD = 0;
    // Configuración SPI como esclavo
    TRISA = 0B00100000; 
    TRISC = 0B00011000; 
    SSPSTAT = 0B00000000; 
    SSPCON2 = 0; 
    SSPCON = 0B00110100; 
        
    // Configuración para interrupciones en donde funcionaran los botones
    PIE1 = 0B00001000; 
    IOCB = 0B00000011; 
    INTCON = 0B11001000;
}
//En las interrrupciones vamos a hacer que funcione el contador
//y se estarán mandando los datos del SPI
void __interrupt()int1(void) {
    GIE = 0;
    if (1 == RBIF) {
        if (1 == RB0) {
            contador--;
            PORTD = contador;
        }
        if (1 == RB1) {
            contador++;
            PORTD = contador;
        }
        RBIF = 0;
    }
    if (1 == SSPIF) {
        spidatos = SSPBUF;
        SSPBUF = contador;
        SSPIF = 0;
    }
    GIE = 0;
}


//-----------------------------------------------------------------------------
//Loop Principal 
//--------------------------------------------
//Llamamos el setup y dejamos que funcione el contador y ya
void main(void) {
    Setup();
    while(1){
      PORTD = contador;
      }
}
